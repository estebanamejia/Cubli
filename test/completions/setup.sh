#!/bin/bash
# Setup script to enable completions for Cubli testing

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(dirname "$SCRIPT_DIR")"

# Detect shell
if [ -n "$ZSH_VERSION" ]; then
    SHELL_TYPE="zsh"
    RC_FILE="$HOME/.zshrc"
elif [ -n "$BASH_VERSION" ]; then
    SHELL_TYPE="bash"
    RC_FILE="$HOME/.bashrc"
else
    echo "Unable to detect shell type"
    exit 1
fi

echo "Detected shell: $SHELL_TYPE"
echo "RC file: $RC_FILE"

# Completion source line
COMPLETION_LINE="source \"$SCRIPT_DIR/load_completions.sh\""

# Check if already installed
if grep -q "load_completions.sh" "$RC_FILE" 2>/dev/null; then
    echo "✓ Completions already installed"
else
    echo "Installing completions..."
    echo "" >> "$RC_FILE"
    echo "# Cubli test completions" >> "$RC_FILE"
    echo "$COMPLETION_LINE" >> "$RC_FILE"
    echo "✓ Completions installed"
fi

echo ""
echo "To enable completions in your current session, run:"
echo "  source \"$SCRIPT_DIR/load_completions.sh\""
echo ""
echo "Or restart your shell."
