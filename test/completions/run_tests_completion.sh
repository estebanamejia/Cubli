#!/bin/bash
# Bash completion for run_tests.sh

_run_tests_completion() {
    local cur prev opts test_targets
    COMPREPLY=()
    cur="${COMP_WORDS[COMP_CWORD]}"
    prev="${COMP_WORDS[COMP_CWORD-1]}"
    
    # Options
    opts="--verbose --no-log --help -v -h"
    
    # Test targets
    test_targets="unit systems all"
    
    # Complete options
    if [[ ${cur} == -* ]]; then
        COMPREPLY=( $(compgen -W "${opts}" -- ${cur}) )
    else
        # Complete test targets
        COMPREPLY=( $(compgen -W "${test_targets}" -- ${cur}) )
    fi
    
    return 0
}

complete -F _run_tests_completion ./test/run_tests.sh
complete -F _run_tests_completion run_tests.sh
