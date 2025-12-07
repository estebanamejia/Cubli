#!/bin/bash
# Setup script for Cubli project
# This extracts and prepares all dependencies for building

set -e  # Exit on first error

echo "Setting up Cubli project dependencies..."
echo ""

# Extract Eigen if not already extracted
if [ ! -d "third-party/eigen/Eigen" ]; then
    echo "→ Extracting Eigen library..."
    cd third-party/eigen
    unzip -q ../../eigen-3.4.0.zip
    # The zip extracts to eigen-3.4.0, rename it to Eigen
    if [ -d "eigen-3.4.0" ]; then
        mv eigen-3.4.0/Eigen .
        rm -rf eigen-3.4.0
    fi
    cd ../..
    echo "  ✓ Eigen extracted"
else
    echo "✓ Eigen already present"
fi

echo ""

# Setup RBDL - check if src is missing (even if other files exist)
if [ ! -d "third-party/rbdl/src" ] || [ ! -f "third-party/rbdl/include/rbdl/rbdl.h" ]; then
    echo "→ Setting up RBDL library..."
    
    # Check if git is available and clone RBDL
    if command -v git &> /dev/null; then
        echo "  Cloning RBDL repository..."
        
        # Clone to temp location
        RBDL_TEMP_DIR=$(mktemp -d)
        git clone https://github.com/rbdl/rbdl.git "$RBDL_TEMP_DIR" 2>&1 | grep -E "(Cloning|error)" || true
        
        # Copy src directory
        if [ -d "$RBDL_TEMP_DIR/src" ]; then
            mkdir -p third-party/rbdl/src
            cp -r "$RBDL_TEMP_DIR/src"/* third-party/rbdl/src/
            echo "  ✓ RBDL source copied"
        else
            echo "  Warning: Could not find src in cloned RBDL"
            mkdir -p third-party/rbdl/src
        fi
        
        # Copy include directory
        if [ -d "$RBDL_TEMP_DIR/include/rbdl" ]; then
            mkdir -p third-party/rbdl/include/rbdl
            cp -r "$RBDL_TEMP_DIR/include/rbdl"/* third-party/rbdl/include/rbdl/
            echo "  ✓ RBDL headers copied"
        fi
        
        # Clean up temp directory
        rm -rf "$RBDL_TEMP_DIR"
    else
        echo "  ! Git not found, creating empty directories"
        mkdir -p third-party/rbdl/{src,include/rbdl}
    fi
    
    echo "  ✓ RBDL setup complete"
else
    echo "✓ RBDL already present"
fi

echo ""

# Generate rbdl_config.h if not present
if [ ! -f "third-party/rbdl/include/rbdl/rbdl_config.h" ]; then
    echo "→ Generating RBDL configuration header..."
    mkdir -p third-party/rbdl/include/rbdl
    cat > third-party/rbdl/include/rbdl/rbdl_config.h << 'EOF'
#ifndef RBDL_CONFIG_H
#define RBDL_CONFIG_H

#define RBDL_BUILD_TYPE "Release"
#define RBDL_VERSION "2.6.0"
#define RBDL_API_VERSION 0x00020600
#define RBDL_BUILD_COMMIT "unknown"
#define RBDL_BUILD_BRANCH "unknown"
#define RBDL_DLLAPI

#endif /* RBDL_CONFIG_H */
EOF
    echo "  ✓ Configuration header generated"
fi

echo ""
echo "✅ Setup complete!"
echo ""
echo "Next steps:"
echo "  bazel build //main:main       # Build the main executable"
echo ""
