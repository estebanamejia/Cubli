#!/bin/bash
# Enhanced test runner with verbose output, similar to pytest

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(dirname "$SCRIPT_DIR")"

# Color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Defaults
TEST_TARGET=""
VERBOSE=false
SHOW_LOG=true

# Parse arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --verbose|-v)
            VERBOSE=true
            shift
            ;;
        --no-log)
            SHOW_LOG=false
            shift
            ;;
        --help|-h)
            echo "Usage: ./test/run_tests.sh [OPTIONS] [TEST_TARGET]"
            echo ""
            echo "Options:"
            echo "  --verbose, -v         Show verbose test output"
            echo "  --no-log              Don't show test log even on failure"
            echo "  --help, -h            Show this help message"
            echo ""
            echo "Test Targets (if not specified, runs all):"
            echo "  unit                  Run unit tests"
            echo "  systems               Run systems tests"
            echo "  all                   Run all tests"
            echo ""
            echo "Examples:"
            echo "  ./test/run_tests.sh unit"
            echo "  ./test/run_tests.sh systems --verbose"
            echo "  ./test/run_tests.sh --verbose"
            exit 0
            ;;
        *)
            TEST_TARGET=$1
            shift
            ;;
    esac
done

run_test() {
    local test_path=$1
    local test_name=$(basename "$test_path" | cut -d: -f2)
    
    echo -e "${BLUE}Running: $test_path${NC}"
    
    if [[ "$VERBOSE" == true ]]; then
        bazel test "$test_path" --test_output=all
    else
        if bazel test "$test_path" 2>&1 | tee /tmp/bazel_test_output.txt; then
            echo -e "${GREEN}✓ PASSED${NC}: $test_name"
            return 0
        else
            echo -e "${RED}✗ FAILED${NC}: $test_name"
            if [[ "$SHOW_LOG" == true ]]; then
                echo -e "${YELLOW}Test output:${NC}"
                grep -A 100 "FAILED\|Error\|Assertion" /tmp/bazel_test_output.txt || cat /tmp/bazel_test_output.txt
            fi
            return 1
        fi
    fi
}

cd "$REPO_ROOT"

FAILED=0

case "$TEST_TARGET" in
    unit)
        run_test "//test/unit:pose_test" || FAILED=$((FAILED + 1))
        ;;
    systems)
        run_test "//test/systems:cubli_test" || FAILED=$((FAILED + 1))
        ;;
    all|"")
        echo -e "${BLUE}=== Running all tests ===${NC}"
        run_test "//test/unit:pose_test" || FAILED=$((FAILED + 1))
        run_test "//test/systems:cubli_test" || FAILED=$((FAILED + 1))
        ;;
    *)
        echo -e "${RED}Unknown test target: $TEST_TARGET${NC}"
        exit 1
        ;;
esac

echo ""
if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}All tests passed!${NC}"
    exit 0
else
    echo -e "${RED}$FAILED test(s) failed${NC}"
    exit 1
fi
