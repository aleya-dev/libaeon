#!/bin/bash

CLANG_FORMAT="clang-format"

function format {
    DIRECTORY=$1
    echo "Formatting code under $DIRECTORY/"
    find "$DIRECTORY" \( -name '*.h' -or -name '*.cpp' \) -print0 | xargs -0 "$CLANG_FORMAT" -i

    for f in $(find "$DIRECTORY" -name '*.h' -or -name '*.cpp'); do
        echo "$f";
        clang-tidy --fix --fix-errors "$f" --header-filter=^\/home\/robindegen\/libaeon\/src\/.* -p build
    done
}

format $(pwd)/src
