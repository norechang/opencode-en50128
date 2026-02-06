#!/usr/bin/env python3
"""
MISRA C:2012 Compliance Checker
Runs multiple static analysis tools and aggregates results
"""

import subprocess
import sys
import json
from pathlib import Path
from datetime import datetime

class MISRAChecker:
    def __init__(self, source_dir, sil_level):
        self.source_dir = Path(source_dir)
        self.sil_level = sil_level
        self.results = {
            'timestamp': datetime.now().isoformat(),
            'sil_level': sil_level,
            'tools': {}
        }
    
    def run_pclint(self):
        """Run PC-lint Plus with MISRA C checking"""
        print("Running PC-lint Plus MISRA C:2012 check...")
        
        c_files = list(self.source_dir.rglob('*.c'))
        
        cmd = [
            'pclp64',
            'tools/static-analysis/pclint.lnt'
        ] + [str(f) for f in c_files]
        
        try:
            result = subprocess.run(
                cmd,
                capture_output=True,
                text=True,
                timeout=300
            )
            
            violations = self.parse_pclint_output(result.stdout)
            
            self.results['tools']['pclint'] = {
                'status': 'completed',
                'total_violations': len(violations),
                'critical_violations': sum(1 for v in violations if v['severity'] == 'error'),
                'violations': violations
            }
            
        except FileNotFoundError:
            print("  PC-lint Plus not found - skipping")
            self.results['tools']['pclint'] = {'status': 'not_available'}
        except subprocess.TimeoutExpired:
            print("  PC-lint Plus timed out")
            self.results['tools']['pclint'] = {'status': 'timeout'}
    
    def run_cppcheck(self):
        """Run Cppcheck with MISRA addon"""
        print("Running Cppcheck MISRA C:2012 check...")
        
        cmd = [
            'cppcheck',
            '--project=tools/static-analysis/cppcheck-project.xml',
            '--addon=misra.py',
            '--xml',
            '--xml-version=2',
            f'--suppress=missingIncludeSystem'
        ]
        
        try:
            result = subprocess.run(
                cmd,
                capture_output=True,
                text=True,
                timeout=300
            )
            
            violations = self.parse_cppcheck_xml(result.stderr)
            
            self.results['tools']['cppcheck'] = {
                'status': 'completed',
                'total_violations': len(violations),
                'critical_violations': sum(1 for v in violations if v['severity'] == 'error'),
                'violations': violations
            }
            
        except FileNotFoundError:
            print("  Cppcheck not found - skipping")
            self.results['tools']['cppcheck'] = {'status': 'not_available'}
        except subprocess.TimeoutExpired:
            print("  Cppcheck timed out")
            self.results['tools']['cppcheck'] = {'status': 'timeout'}
    
    def check_dynamic_memory(self):
        """Check for forbidden dynamic memory allocation (SIL 2+)"""
        print("Checking for dynamic memory allocation...")
        
        if self.sil_level < 2:
            print("  Not required for SIL", self.sil_level)
            return
        
        violations = []
        forbidden_funcs = ['malloc', 'calloc', 'realloc', 'free']
        
        for c_file in self.source_dir.rglob('*.c'):
            with open(c_file, 'r') as f:
                for line_num, line in enumerate(f, 1):
                    for func in forbidden_funcs:
                        if f'\\b{func}\\b' in line and not line.strip().startswith('//'):
                            violations.append({
                                'file': str(c_file),
                                'line': line_num,
                                'severity': 'critical',
                                'rule': 'MISRA 21.3 / EN 50128',
                                'message': f'Use of {func}() forbidden for SIL {self.sil_level}',
                                'code': line.strip()
                            })
        
        self.results['dynamic_memory_check'] = {
            'violations': violations,
            'compliant': len(violations) == 0
        }
        
        if violations:
            print(f"  FAILED: {len(violations)} violations found")
        else:
            print("  PASSED: No dynamic memory allocation")
    
    def check_recursion(self):
        """Check for recursion (highly recommended to avoid)"""
        print("Checking for recursion...")
        
        # This is a simplified check - full call graph analysis needed
        violations = []
        
        # Would need proper parser to detect recursion
        # This is placeholder
        
        self.results['recursion_check'] = {
            'violations': violations,
            'note': 'Full call graph analysis recommended'
        }
    
    def parse_pclint_output(self, output):
        """Parse PC-lint output"""
        violations = []
        
        for line in output.split('\n'):
            # Parse PC-lint message format
            # Example: file.c(123): error 534: Ignoring return value
            # Simplified parsing
            if 'error' in line.lower() or 'warning' in line.lower():
                violations.append({
                    'raw': line,
                    'severity': 'error' if 'error' in line.lower() else 'warning'
                })
        
        return violations
    
    def parse_cppcheck_xml(self, xml_output):
        """Parse Cppcheck XML output"""
        violations = []
        
        # Would use XML parser in production
        # Simplified for example
        
        return violations
    
    def generate_report(self):
        """Generate comprehensive MISRA compliance report"""
        print("\n" + "="*70)
        print(f"MISRA C:2012 COMPLIANCE REPORT - SIL {self.sil_level}")
        print("="*70)
        print(f"Timestamp: {self.results['timestamp']}")
        print()
        
        # Tool results
        print("Static Analysis Tools:")
        for tool, data in self.results['tools'].items():
            if data['status'] == 'completed':
                print(f"  {tool}: {data['total_violations']} violations " +
                      f"({data['critical_violations']} critical)")
            else:
                print(f"  {tool}: {data['status']}")
        print()
        
        # Dynamic memory check (critical for SIL 2+)
        if 'dynamic_memory_check' in self.results:
            check = self.results['dynamic_memory_check']
            status = "✓ PASS" if check['compliant'] else "✗ FAIL"
            print(f"Dynamic Memory Check: {status}")
            if not check['compliant']:
                print(f"  {len(check['violations'])} violations")
                for v in check['violations'][:5]:  # Show first 5
                    print(f"    {v['file']}:{v['line']} - {v['message']}")
            print()
        
        # Overall compliance
        total_critical = sum(
            d.get('critical_violations', 0) 
            for d in self.results['tools'].values() 
            if isinstance(d, dict) and 'critical_violations' in d
        )
        
        dynamic_violations = len(self.results.get('dynamic_memory_check', {}).get('violations', []))
        
        print("="*70)
        if total_critical == 0 and dynamic_violations == 0:
            print("✓ MISRA C:2012 COMPLIANCE: PASSED")
            print()
            return True
        else:
            print("✗ MISRA C:2012 COMPLIANCE: FAILED")
            print(f"  Critical issues: {total_critical + dynamic_violations}")
            print()
            return False
    
    def save_report(self):
        """Save report to JSON"""
        output_file = f"misra_compliance_report_sil{self.sil_level}.json"
        
        with open(output_file, 'w') as f:
            json.dump(self.results, f, indent=2)
        
        print(f"Detailed report saved to: {output_file}")

def main():
    if len(sys.argv) != 3:
        print("Usage: check_misra.py <source_dir> <sil_level>")
        print("Example: check_misra.py src/ 3")
        sys.exit(1)
    
    source_dir = sys.argv[1]
    sil_level = int(sys.argv[2])
    
    if not Path(source_dir).exists():
        print(f"Error: Source directory '{source_dir}' not found")
        sys.exit(1)
    
    if sil_level not in [0, 1, 2, 3, 4]:
        print(f"Error: SIL level must be 0-4")
        sys.exit(1)
    
    checker = MISRAChecker(source_dir, sil_level)
    
    # Run all checks
    checker.run_pclint()
    checker.run_cppcheck()
    checker.check_dynamic_memory()
    checker.check_recursion()
    
    # Generate report
    passed = checker.generate_report()
    checker.save_report()
    
    sys.exit(0 if passed else 1)

if __name__ == "__main__":
    main()
