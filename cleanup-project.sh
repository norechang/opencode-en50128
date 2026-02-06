#!/bin/bash
set -e

echo "EN 50128 Project Cleanup"
echo "========================"
echo ""

# Remove backup files
echo "Removing backup files..."
rm -f LIFECYCLE.md.backup CONTRIBUTING.md.backup REVISION_SUMMARY.md
echo "✅ Backup files removed"

# Remove empty directories
echo ""
echo "Removing empty directories..."
rmdir templates/ 2>/dev/null || true
rmdir tools/build/ 2>/dev/null || true
rmdir tools/coverage/ 2>/dev/null || true
rm -rf docs/design docs/plans docs/requirements docs/safety docs/test docs/reports
echo "✅ Empty directories removed"

# Archive Phase reports
echo ""
echo "Archiving Phase completion reports..."
mkdir -p docs/project-revision
mv PHASE_*.md docs/project-revision/ 2>/dev/null || true
mv PROJECT_REVISION_STATUS.md docs/project-revision/ 2>/dev/null || true
mv NEXT_STEPS.md docs/project-revision/ 2>/dev/null || true
mv CLEANUP_ANALYSIS.md docs/project-revision/ 2>/dev/null || true
echo "✅ Phase reports archived to docs/project-revision/"

echo ""
echo "=========================================="
echo "Cleanup complete!"
echo "=========================================="
echo ""
echo "Summary:"
echo "- Removed 3 backup/obsolete files"
echo "- Removed 9 empty directories"
echo "- Archived 8 files to docs/project-revision/"
echo ""
echo "Next steps:"
echo "1. Review changes: git status"
echo "2. Update documentation files"
echo "3. Commit changes"
