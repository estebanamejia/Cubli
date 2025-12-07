# Cubli Development Aliases & Functions
# Add these to your ~/.bashrc or ~/.zshrc for quick access

# Quick test aliases
alias t='./test/run_tests.sh'
alias tu='./test/run_tests.sh unit'
alias ts='./test/run_tests.sh systems'
alias tv='./test/run_tests.sh --verbose'
alias tq='./test/quick_test.sh'

# Build aliases
alias bb='bazel build //...'
alias bc='bazel clean'
alias br='bazel run'

# Test functions with common patterns
function tfilter() {
    # Run a specific test with filter
    # Usage: tfilter systems '*BasicAssert*'
    local target=$1
    local filter=$2
    ./test/quick_test.sh "$target" --gtest_filter="$filter"
}

function twatch() {
    # Run tests on file changes (requires entr)
    # Usage: twatch unit
    local target=$1
    find . -name "*.cpp" -o -name "*.h" | entr -c ./test/run_tests.sh "$target"
}

function tbuild() {
    # Build a specific target
    # Usage: tbuild //math:math
    bazel build "$@"
}

# Navigation shortcuts
alias cd_cubli='cd ~/Cubli'
alias cd_tests='cd ~/Cubli/test'
alias cd_core='cd ~/Cubli/cubli_core'
alias cd_math='cd ~/Cubli/math'
