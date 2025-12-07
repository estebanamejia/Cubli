#!/bin/bash
# Load all completion scripts and aliases for Cubli testing

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Source all files except setup.sh and this file
for script_file in "$SCRIPT_DIR"/*.sh; do
    if [ -f "$script_file" ]; then
        case "$(basename "$script_file")" in
            load_completions.sh|setup.sh)
                continue
                ;;
            *)
                source "$script_file"
                ;;
        esac
    fi
done
