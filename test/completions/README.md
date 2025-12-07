# Cubli Testing & Development QoL Setup

This directory contains quality-of-life improvements for testing and development.

## Quick Setup

**Install completions and aliases (one-time setup):**
```bash
./completions/setup.sh
```

Then restart your shell or run:
```bash
source ./completions/load_completions.sh
```

## Features

### Tab Completion
- `./test/run_tests.sh <TAB>` - Complete test targets (unit, systems, all)
- `./test/run_tests.sh --<TAB>` - Complete flags (--verbose, --no-log, --help)
- `./test/quick_test.sh <TAB>` - Complete test targets
- `./test/quick_test.sh systems --<TAB>` - Complete gtest options

### Aliases
Short aliases for common commands:

| Alias | Command | Purpose |
|-------|---------|---------|
| `t` | `./test/run_tests.sh` | Run all tests |
| `tu` | `./test/run_tests.sh unit` | Run unit tests |
| `ts` | `./test/run_tests.sh systems` | Run systems tests |
| `tv` | `./test/run_tests.sh --verbose` | Run with verbose output |
| `tq` | `./test/quick_test.sh` | Quick test runner |
| `bb` | `bazel build //...` | Build everything |
| `bc` | `bazel clean` | Clean build artifacts |

### Functions
Handy functions for common workflows:

**Filter tests:**
```bash
tfilter systems '*BasicAssert*'    # Run specific test by filter
tfilter unit '*Pose*'               # Filter unit tests
```

**Watch for changes** (requires `entr`):
```bash
twatch unit                         # Rerun unit tests on file changes
twatch systems                      # Rerun systems tests on file changes
```

**Build targets:**
```bash
tbuild //math:math                  # Build specific target
tbuild //...                        # Build everything
```

**Navigation shortcuts:**
```bash
cd_cubli                            # Jump to repo root
cd_tests                            # Jump to test directory
cd_core                             # Jump to cubli_core
cd_math                             # Jump to math directory
```

## Manual Installation

If you prefer to install manually, add this to your `~/.bashrc` or `~/.zshrc`:

```bash
source ~/Cubli/test/completions/load_completions.sh
```

Then reload your shell:
```bash
exec $SHELL
```

## Examples

**Run all tests:**
```bash
t
```

**Run unit tests verbosely:**
```bash
tv unit
# or
tu --verbose
```

**Debug a specific test:**
```bash
tfilter systems 'StabilityTest.BasicAssertions'
```

**Watch and re-run tests:**
```bash
twatch unit
# Tests will re-run whenever .cpp or .h files change
```

**Build and test:**
```bash
bb && t
```
