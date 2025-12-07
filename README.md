# Cubli

A rigid body dynamics project built with Bazel.

## Quick Start

### Prerequisites

You'll need:
- Bazel 7.x or higher (see `.bazelversion`)
- Git
- A C++ compiler (gcc/clang)
- unzip

### Setup & Build

1. **Clone the repository**
   ```bash
   git clone https://github.com/estebanamejia/Cubli.git
   cd Cubli
   ```

2. **Run the setup script**
   ```bash
   ./setup.sh
   ```
   This will:
   - Extract the Eigen library
   - Download and prepare RBDL dependencies
   - Generate necessary configuration files

3. **Build the project**
   ```bash
   bazel build //main:main
   ```

4. **Run the executable**
   ```bash
   ./bazel-bin/main/main
   ```

## Project Structure

- `cubli_core/` - Core Cubli library
- `math/` - Mathematical utilities (Point, Pose, Frame)
- `main/` - Main executable
- `test/` - Unit and integration tests
- `third-party/` - External dependencies (Eigen, RBDL)

## Available Build Targets

```bash
# Build everything
bazel build //...

# Build specific targets
bazel build //main:main                    # Build main executable
bazel build //cubli_core:cubli_core        # Build core library
bazel build //math:math                    # Build math library
bazel build //test/unit/...                # Build unit tests
bazel build //test/systems/...             # Build system tests
```

## Troubleshooting

If the build fails:

1. Ensure `setup.sh` ran successfully: `./setup.sh`
2. Check your Bazel version: `bazel --version`
3. Clean and rebuild: `bazel clean && bazel build //main:main`

For more details, see the build scripts in `build_scripts/`