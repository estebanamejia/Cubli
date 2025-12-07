#!/bin/bash
# Bash completion for quick_test.sh

_quick_test_completion() {
    local cur prev opts test_targets
    COMPREPLY=()
    cur="${COMP_WORDS[COMP_CWORD]}"
    prev="${COMP_WORDS[COMP_CWORD-1]}"
    
    # Test targets
    test_targets="unit systems"
    
    # Complete test targets first
    if [ $COMP_CWORD -eq 1 ]; then
        COMPREPLY=( $(compgen -W "${test_targets}" -- ${cur}) )
    else
        # After test target, suggest gtest options
        if [[ ${cur} == -* ]]; then
            COMPREPLY=( $(compgen -W "--gtest_filter=" -- ${cur}) )
        fi
    fi
    
    return 0
}

complete -F _quick_test_completion ./test/quick_test.sh
complete -F _quick_test_completion quick_test.sh
