#!/bin/bash
# Quick test runner with verbose output - similar to pytest -k PATTERN

set -e

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m'

if [ $# -lt 1 ]; then
    echo "Usage: $0 <test_target> [gtest_args...]"
    echo ""
    echo "Examples:"
    echo "  $0 unit"
    echo "  $0 systems"
    echo "  $0 unit --gtest_filter='*Pose*'"
    echo "  $0 systems --gtest_filter='StabilityTest.BasicAssertions'"
    exit 1
fi

TEST_TARGET=$1
shift  # Remove first arg
EXTRA_ARGS="$@"

cd "$REPO_ROOT"

case "$TEST_TARGET" in
    unit)
        TARGET="//test/unit:pose_test"
        ;;
    systems)
        TARGET="//test/systems:cubli_test"
        ;;
    *)
        echo -e "${RED}Unknown test: $TEST_TARGET${NC}"
        exit 1
        ;;
esac

echo -e "${BLUE}Running: $TARGET${NC}"
echo -e "${BLUE}Args: $EXTRA_ARGS${NC}"
echo ""

bazel test "$TARGET" --test_output=all $EXTRA_ARGS
