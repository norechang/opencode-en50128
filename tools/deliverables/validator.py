"""
Validate deliverable YAML files against schema.

Usage:
    # Validate single file
    python3 tools/deliverables/validator.py deliverables/requirements/Software-Requirements-Specification.yaml
    
    # Validate all deliverables
    python3 tools/deliverables/validator.py --all
"""

import yaml
import jsonschema
import sys
from pathlib import Path
from typing import List, Tuple, Dict


class DeliverableValidator:
    """Validate deliverable definitions against schema."""
    
    def __init__(self, schema_path: Path):
        """
        Initialize validator.
        
        Args:
            schema_path: Path to deliverable-schema.yaml
        """
        with open(schema_path, 'r') as f:
            self.schema = yaml.safe_load(f)
    
    def validate_file(self, deliverable_file: Path) -> Tuple[bool, List[str]]:
        """
        Validate a deliverable YAML file.
        
        Args:
            deliverable_file: Path to deliverable YAML file
        
        Returns:
            (is_valid, error_messages)
        """
        try:
            with open(deliverable_file, 'r') as f:
                data = yaml.safe_load(f)
        except yaml.YAMLError as e:
            return False, [f"YAML parse error: {e}"]
        except Exception as e:
            return False, [f"File read error: {e}"]
        
        if data is None:
            return False, ["Empty YAML file"]
        
        errors = []
        try:
            jsonschema.validate(instance=data, schema=self.schema)
            return True, []
        except jsonschema.ValidationError as e:
            errors.append(f"Validation error at {'.'.join(str(p) for p in e.path)}: {e.message}")
            return False, errors
        except jsonschema.SchemaError as e:
            errors.append(f"Schema error: {e.message}")
            return False, errors
    
    def validate_all(self, deliverables_dir: Path) -> Dict[str, Tuple[bool, List[str]]]:
        """
        Validate all deliverable YAML files.
        
        Args:
            deliverables_dir: Path to deliverables/ directory
        
        Returns:
            Dictionary mapping file path to (is_valid, errors)
        """
        results = {}
        for yaml_file in deliverables_dir.rglob("*.yaml"):
            # Skip schema files
            if yaml_file.parent.name == 'schema':
                continue
            
            is_valid, errors = self.validate_file(yaml_file)
            results[str(yaml_file.relative_to(deliverables_dir))] = (is_valid, errors)
        
        return results


def main():
    """Command-line interface."""
    import argparse
    
    parser = argparse.ArgumentParser(
        description='Validate EN 50128 deliverable YAML files'
    )
    parser.add_argument(
        'file',
        nargs='?',
        type=Path,
        help='Path to deliverable YAML file to validate'
    )
    parser.add_argument(
        '--all',
        action='store_true',
        help='Validate all deliverable files'
    )
    parser.add_argument(
        '--deliverables-dir',
        type=Path,
        default=Path(__file__).parent.parent.parent / 'deliverables',
        help='Path to deliverables directory (default: ../../deliverables)'
    )
    
    args = parser.parse_args()
    
    # Find schema
    schema_path = args.deliverables_dir / 'schema' / 'deliverable-schema.yaml'
    if not schema_path.exists():
        print(f"❌ Schema not found: {schema_path}", file=sys.stderr)
        sys.exit(1)
    
    validator = DeliverableValidator(schema_path)
    
    if args.all:
        # Validate all deliverables
        print(f"Validating all deliverables in {args.deliverables_dir}...")
        results = validator.validate_all(args.deliverables_dir)
        
        valid_count = sum(1 for is_valid, _ in results.values() if is_valid)
        total_count = len(results)
        
        print(f"\n📊 Results: {valid_count}/{total_count} valid\n")
        
        for file_path, (is_valid, errors) in sorted(results.items()):
            if is_valid:
                print(f"✅ {file_path}")
            else:
                print(f"❌ {file_path}")
                for error in errors:
                    print(f"   {error}")
        
        sys.exit(0 if valid_count == total_count else 1)
    
    elif args.file:
        # Validate single file
        if not args.file.exists():
            print(f"❌ File not found: {args.file}", file=sys.stderr)
            sys.exit(1)
        
        print(f"Validating {args.file}...")
        is_valid, errors = validator.validate_file(args.file)
        
        if is_valid:
            print("✅ Valid deliverable definition")
            sys.exit(0)
        else:
            print("❌ Validation failed:")
            for error in errors:
                print(f"   {error}")
            sys.exit(1)
    
    else:
        parser.print_help()
        sys.exit(1)


if __name__ == '__main__':
    main()
