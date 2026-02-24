"""
c_parser.py - C source code parser for MC/DC expression extraction.

Approach:
  1. Run gcc -E to preprocess the file (resolves includes, macros)
  2. Parse the preprocessed output with pycparser
  3. Walk the AST to find all compound boolean expressions (&&, ||)
  4. Extract the top-level expression, its sub-conditions, location info

Falls back to regex-based extraction if pycparser fails (e.g. non-standard
compiler extensions that pycparser cannot handle).
"""

from __future__ import annotations

import os
import re
import subprocess
import sys
import tempfile
from dataclasses import dataclass, field
from pathlib import Path
from typing import List, Optional

try:
    import pycparser
    from pycparser import c_ast, parse_file
    PYCPARSER_AVAILABLE = True
except ImportError:
    PYCPARSER_AVAILABLE = False


# ---------------------------------------------------------------------------
# Data structures
# ---------------------------------------------------------------------------

@dataclass
class Condition:
    """A single atomic boolean condition within a compound expression."""
    text: str           # Source text of the condition (best-effort)
    index: int          # 0-based index within the parent expression


@dataclass
class Expression:
    """A compound boolean expression extracted from C source."""
    expr_id: str                    # e.g. "CBE-SM-001"
    file: str                       # relative or absolute source path
    line: int                       # 1-based line number
    function: str                   # enclosing function name (best-effort)
    text: str                       # full expression text (best-effort)
    conditions: List[Condition]     # atomic conditions
    operator: str                   # "AND", "OR", "MIXED"
    num_conditions: int             # len(conditions)

    def __post_init__(self):
        self.num_conditions = len(self.conditions)


# ---------------------------------------------------------------------------
# Regex-based extractor (fallback and primary for this project)
# ---------------------------------------------------------------------------

# Pattern: captures if/while/for/return conditions and assignment RHS that
# contain && or ||.  We deliberately match the outermost () block.
_COMPOUND_RE = re.compile(
    r'(?:if|while|for|return)\s*\((.+)\)',
    re.DOTALL
)

# Simpler line-level scan for && or ||
_BOOL_OP_RE = re.compile(r'&&|\|\|')

# Patterns to split an expression into atomic conditions
# Strip outer parens, then split on top-level && or ||
_SPLIT_AND_RE = re.compile(r'\s*&&\s*')
_SPLIT_OR_RE  = re.compile(r'\s*\|\|\s*')


def _strip_outer_parens(s: str) -> str:
    """Remove one layer of matched outer parentheses if present."""
    s = s.strip()
    if s.startswith('(') and s.endswith(')'):
        # verify they match
        depth = 0
        for i, ch in enumerate(s):
            if ch == '(':
                depth += 1
            elif ch == ')':
                depth -= 1
            if depth == 0 and i < len(s) - 1:
                return s  # outer parens don't span whole string
        return s[1:-1].strip()
    return s


def _split_top_level(expr: str, op: str) -> List[str]:
    """Split expr on top-level occurrences of op ('&&' or '||')."""
    parts = []
    depth = 0
    current = []
    i = 0
    op_len = len(op)
    while i < len(expr):
        ch = expr[i]
        if ch in '([':
            depth += 1
            current.append(ch)
            i += 1
        elif ch in ')]':
            depth -= 1
            current.append(ch)
            i += 1
        elif depth == 0 and expr[i:i+op_len] == op:
            # check not part of longer op
            if op == '&&' and i > 0 and expr[i-1] == '&':
                current.append(ch)
                i += 1
                continue
            if op == '||' and i > 0 and expr[i-1] == '|':
                current.append(ch)
                i += 1
                continue
            parts.append(''.join(current).strip())
            current = []
            i += op_len
        else:
            current.append(ch)
            i += 1
    if current:
        parts.append(''.join(current).strip())
    return [p for p in parts if p]


def _classify_operator(expr: str) -> str:
    """Return 'AND', 'OR', or 'MIXED' based on top-level operators."""
    has_and = bool(_split_top_level(expr, '&&')[1:]) if '&&' in expr else False
    has_or  = bool(_split_top_level(expr, '||')[1:]) if '||' in expr else False
    # re-check: split gives >1 part only if op exists at top level
    parts_and = _split_top_level(expr, '&&')
    parts_or  = _split_top_level(expr, '||')
    has_and = len(parts_and) > 1
    has_or  = len(parts_or)  > 1
    if has_and and has_or:
        return 'MIXED'
    if has_and:
        return 'AND'
    if has_or:
        return 'OR'
    return 'SIMPLE'


def _extract_conditions(expr: str, operator: str) -> List[Condition]:
    """Split expression into atomic conditions."""
    stripped = _strip_outer_parens(expr)
    if operator == 'AND':
        parts = _split_top_level(stripped, '&&')
    elif operator == 'OR':
        parts = _split_top_level(stripped, '||')
    else:
        # MIXED: split on both, deduplicate while preserving order
        # For truth table, treat each atomic sub-expression as a condition
        parts = _split_top_level(stripped, '&&')
        # Further split each part on ||
        all_parts: List[str] = []
        for p in parts:
            sub = _split_top_level(p.strip(), '||')
            all_parts.extend(sub)
        parts = all_parts

    # Remove empty strings, strip parens from each
    conditions = []
    seen = {}
    for i, part in enumerate(parts):
        text = _strip_outer_parens(part.strip())
        if not text:
            continue
        # Deduplicate: assign same index if repeated
        if text in seen:
            continue
        seen[text] = i
        conditions.append(Condition(text=text, index=len(conditions)))
    return conditions


def _current_function(lines: List[str], lineno: int) -> str:
    """Walk backwards from lineno to find the enclosing function name."""
    # Look for a pattern like: return_type function_name(
    fn_re = re.compile(r'^\s*\w[\w\s\*]*\b(\w+)\s*\(')
    for i in range(lineno - 2, max(0, lineno - 100), -1):
        m = fn_re.match(lines[i])
        if m:
            name = m.group(1)
            # Filter out keywords
            if name not in ('if', 'while', 'for', 'switch', 'return', 'do'):
                return name
    return 'unknown'


def extract_expressions_regex(
    source_files: List[str],
    include_dirs: Optional[List[str]] = None
) -> List[Expression]:
    """
    Extract compound boolean expressions from C source files using regex.

    This is the primary extraction method. pycparser is available as a
    secondary validation path but regex is more robust against non-standard
    extensions in embedded C.
    """
    expressions: List[Expression] = []
    counters: dict = {}  # per-file counters for expr_id generation

    for src_path in source_files:
        path = Path(src_path)
        if not path.exists():
            print(f"[WARN] File not found: {src_path}", file=sys.stderr)
            continue

        try:
            text = path.read_text(encoding='utf-8', errors='replace')
        except OSError as e:
            print(f"[WARN] Cannot read {src_path}: {e}", file=sys.stderr)
            continue

        lines = text.splitlines()
        file_key = path.stem.upper()[:2]  # e.g. "SM" from safety_monitor

        # Build a 2-char module abbreviation from filename
        stem = path.stem  # e.g. safety_monitor
        parts_stem = stem.split('_')
        if len(parts_stem) >= 2:
            abbrev = (parts_stem[0][0] + parts_stem[1][0]).upper()
        else:
            abbrev = stem[:2].upper()

        if abbrev not in counters:
            counters[abbrev] = 0

        # Scan line by line; for multi-line expressions, join continuation lines
        i = 0
        while i < len(lines):
            raw_line = lines[i]
            stripped = raw_line.strip()

            # Skip comment lines and preprocessor directives
            if stripped.startswith('//') or stripped.startswith('#') or stripped.startswith('*'):
                i += 1
                continue

            # Check if this line contains a conditional with && or ||
            if _BOOL_OP_RE.search(stripped):
                # Collect the full statement (may span multiple lines)
                # Look for the complete balanced-paren expression
                combined = stripped
                j = i + 1
                # If the line doesn't have a closing ; or { yet, continue collecting
                open_p = combined.count('(') - combined.count(')')
                while open_p > 0 and j < min(i + 10, len(lines)):
                    next_line = lines[j].strip()
                    if next_line.startswith('//') or next_line.startswith('*'):
                        j += 1
                        continue
                    combined = combined + ' ' + next_line
                    open_p = combined.count('(') - combined.count(')')
                    j += 1

                # Extract the boolean expression from the combined line
                expr_text = _extract_bool_expr(combined)
                if expr_text is None:
                    i += 1
                    continue

                # Must have at least 2 conditions (&&/|| at top level)
                operator = _classify_operator(expr_text)
                if operator == 'SIMPLE':
                    i += 1
                    continue

                conditions = _extract_conditions(expr_text, operator)
                if len(conditions) < 2:
                    i += 1
                    continue

                # Get enclosing function
                func_name = _current_function(lines, i + 1)

                counters[abbrev] += 1
                expr_id = f"CBE-{abbrev}-{counters[abbrev]:03d}"

                expressions.append(Expression(
                    expr_id=expr_id,
                    file=str(path),
                    line=i + 1,
                    function=func_name,
                    text=expr_text,
                    conditions=conditions,
                    operator=operator,
                    num_conditions=len(conditions),
                ))

            i += 1

    return expressions


def _extract_bool_expr(line: str) -> Optional[str]:
    """
    Extract the boolean expression from a line like:
      if ((a && b) || c) {
      while (x || y) {
      return (p && q);
    Also handles bare assignments and return statements.
    """
    # Try to find the outermost () after if/while/for/return
    m = re.search(r'(?:if|while|for)\s*\(', line)
    if m:
        start = m.end() - 1  # position of '('
        # Find matching close paren
        depth = 0
        for k in range(start, len(line)):
            if line[k] == '(':
                depth += 1
            elif line[k] == ')':
                depth -= 1
                if depth == 0:
                    inner = line[start+1:k]
                    return inner.strip()
        return None

    # return (expr) or return expr;
    m = re.search(r'return\s+\((.+)\)', line)
    if m:
        return m.group(1).strip()

    m = re.search(r'return\s+(.+?)\s*;', line)
    if m:
        candidate = m.group(1).strip()
        if _BOOL_OP_RE.search(candidate):
            return candidate

    # Bare expression or assignment RHS
    if _BOOL_OP_RE.search(line):
        # Try to find an assignment RHS
        m = re.search(r'=\s*(.+?)\s*;', line)
        if m:
            candidate = m.group(1).strip()
            if _BOOL_OP_RE.search(candidate):
                return candidate
        # Last resort: just return the line stripped of ; and {}
        cleaned = line.rstrip(';{').strip()
        return cleaned if _BOOL_OP_RE.search(cleaned) else None

    return None


# ---------------------------------------------------------------------------
# pycparser-based extractor (optional, for validation)
# ---------------------------------------------------------------------------

class _BoolExprVisitor(c_ast.NodeVisitor):
    """AST visitor that collects compound boolean expressions."""

    def __init__(self, filename: str):
        self.filename = filename
        self.found: List[dict] = []
        self._current_func = 'unknown'

    def visit_FuncDef(self, node):
        prev = self._current_func
        self._current_func = node.decl.name if node.decl else 'unknown'
        self.generic_visit(node)
        self._current_func = prev

    def _has_bool_op(self, node) -> bool:
        if isinstance(node, c_ast.BinaryOp):
            if node.op in ('&&', '||'):
                return True
            return self._has_bool_op(node.left) or self._has_bool_op(node.right)
        return False

    def _is_compound_bool(self, node) -> bool:
        """True if node is a && or || at the top level."""
        return isinstance(node, c_ast.BinaryOp) and node.op in ('&&', '||')

    def _collect_conditions(self, node, op: str) -> List[str]:
        """Collect atomic conditions from a homogeneous && or || tree."""
        if isinstance(node, c_ast.BinaryOp) and node.op == op:
            return (self._collect_conditions(node.left, op) +
                    self._collect_conditions(node.right, op))
        # Leaf: generate text representation
        return [self._node_text(node)]

    def _node_text(self, node) -> str:
        """Best-effort text from AST node."""
        if isinstance(node, c_ast.BinaryOp):
            return f"({self._node_text(node.left)} {node.op} {self._node_text(node.right)})"
        if isinstance(node, c_ast.UnaryOp):
            return f"{node.op}({self._node_text(node.expr)})"
        if isinstance(node, c_ast.ID):
            return node.name
        if isinstance(node, c_ast.Constant):
            return node.value
        if isinstance(node, c_ast.StructRef):
            return f"{self._node_text(node.name)}{node.type}{node.field.name}"
        if hasattr(node, 'coord') and node.coord:
            return f"<expr@{node.coord.line}>"
        return "<expr>"

    def _visit_condition(self, node):
        if node is None:
            return
        if self._is_compound_bool(node):
            op = node.op
            # Find root operator
            top_op = op
            # Check if mixed
            left_has_other = self._has_other_bool_op(node.left, op)
            right_has_other = self._has_other_bool_op(node.right, op)
            if left_has_other or right_has_other:
                operator = 'MIXED'
                conditions = self._collect_all_atomic(node)
            else:
                operator = 'AND' if op == '&&' else 'OR'
                conditions = self._collect_conditions(node, op)

            if len(conditions) >= 2:
                coord = node.coord
                line = coord.line if coord else 0
                self.found.append({
                    'line': line,
                    'function': self._current_func,
                    'text': self._node_text(node),
                    'conditions': conditions,
                    'operator': operator,
                })

    def _has_other_bool_op(self, node, current_op: str) -> bool:
        if isinstance(node, c_ast.BinaryOp):
            other = '||' if current_op == '&&' else '&&'
            if node.op == other:
                return True
            return (self._has_other_bool_op(node.left, current_op) or
                    self._has_other_bool_op(node.right, current_op))
        return False

    def _collect_all_atomic(self, node) -> List[str]:
        """Collect all atomic (non-bool-op) nodes from mixed expression."""
        if isinstance(node, c_ast.BinaryOp) and node.op in ('&&', '||'):
            return self._collect_all_atomic(node.left) + self._collect_all_atomic(node.right)
        return [self._node_text(node)]

    def visit_If(self, node):
        self._visit_condition(node.cond)
        self.generic_visit(node)

    def visit_While(self, node):
        self._visit_condition(node.cond)
        self.generic_visit(node)

    def visit_For(self, node):
        self._visit_condition(node.cond)
        self.generic_visit(node)

    def visit_Return(self, node):
        if node.expr:
            self._visit_condition(node.expr)
        self.generic_visit(node)


def extract_expressions_pycparser(
    source_files: List[str],
    include_dirs: Optional[List[str]] = None
) -> List[Expression]:
    """
    Extract compound boolean expressions using pycparser (AST-based).
    Falls back to regex on parse error.
    """
    if not PYCPARSER_AVAILABLE:
        print("[INFO] pycparser not available, using regex fallback", file=sys.stderr)
        return extract_expressions_regex(source_files, include_dirs)

    expressions: List[Expression] = []
    counters: dict = {}

    inc_args = []
    if include_dirs:
        for d in include_dirs:
            inc_args.extend(['-I', d])

    for src_path in source_files:
        path = Path(src_path)
        if not path.exists():
            print(f"[WARN] File not found: {src_path}", file=sys.stderr)
            continue

        stem = path.stem
        parts_stem = stem.split('_')
        if len(parts_stem) >= 2:
            abbrev = (parts_stem[0][0] + parts_stem[1][0]).upper()
        else:
            abbrev = stem[:2].upper()
        if abbrev not in counters:
            counters[abbrev] = 0

        # Preprocess with gcc -E
        with tempfile.NamedTemporaryFile(suffix='.i', delete=False, mode='w') as tmp:
            tmp_path = tmp.name

        try:
            cmd = ['gcc', '-E', '-std=c11'] + inc_args + [str(path), '-o', tmp_path]
            result = subprocess.run(cmd, capture_output=True, text=True)
            if result.returncode != 0:
                print(f"[WARN] gcc -E failed for {src_path}, using regex fallback",
                      file=sys.stderr)
                exprs = extract_expressions_regex([src_path], include_dirs)
                expressions.extend(exprs)
                continue

            try:
                ast = pycparser.parse_file(tmp_path, use_cpp=False)
            except pycparser.plyparser.ParseError as e:
                print(f"[WARN] pycparser failed for {src_path}: {e}, using regex",
                      file=sys.stderr)
                exprs = extract_expressions_regex([src_path], include_dirs)
                expressions.extend(exprs)
                continue

            visitor = _BoolExprVisitor(str(path))
            visitor.visit(ast)

            for item in visitor.found:
                counters[abbrev] += 1
                expr_id = f"CBE-{abbrev}-{counters[abbrev]:03d}"
                conds = [Condition(text=c, index=k)
                         for k, c in enumerate(item['conditions'])]
                expressions.append(Expression(
                    expr_id=expr_id,
                    file=str(path),
                    line=item['line'],
                    function=item['function'],
                    text=item['text'],
                    conditions=conds,
                    operator=item['operator'],
                    num_conditions=len(conds),
                ))
        finally:
            try:
                os.unlink(tmp_path)
            except OSError:
                pass

    return expressions


# ---------------------------------------------------------------------------
# Public API
# ---------------------------------------------------------------------------

def extract_expressions(
    source_files: List[str],
    include_dirs: Optional[List[str]] = None,
    use_pycparser: bool = False,
) -> List[Expression]:
    """
    Extract all compound boolean expressions from C source files.

    Args:
        source_files:  list of .c file paths
        include_dirs:  list of -I include directories
        use_pycparser: if True, attempt pycparser AST walk (more precise but
                       can fail on non-standard embedded C); defaults to regex

    Returns:
        List of Expression objects, one per compound boolean expression found.
    """
    if use_pycparser and PYCPARSER_AVAILABLE:
        return extract_expressions_pycparser(source_files, include_dirs)
    return extract_expressions_regex(source_files, include_dirs)
