#!/bin/bash

if [ "$1" != "" ]; then
    if [ -d libtest$1 ]; then
        mkdir -p test/odvd/reference/Test$1
            cd libtest$1
            cp -r include ../test/odvd/reference/Test$1
            cp -r src ../test/odvd/reference/Test$1
            cd ..
        mkdir -p test/odvd/reference/Test$1_withCMake
            cp -r libtest$1 test/odvd/reference/Test$1_withCMake/
    fi
fi

