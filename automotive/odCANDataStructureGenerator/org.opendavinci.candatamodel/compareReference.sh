#!/bin/bash

if [ "$1" != "" ]; then
    if [ -d libtest$1 ]; then
	diff -Naur test/odvd/reference/Test$1_withCMake/libtest$1 libtest$1
    fi
fi

