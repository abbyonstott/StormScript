#!/bin/bash

if [ ! "$1" = "--prefix" ]; then
    echo "Expected prefix argument."
    exit 1;
else 
    rm -rf ./CMakeFiles
    rm -rf CMakeCache.txt
    rm Makefile

    cmake ..
    make -j $(nproc)

    if [ ! -e "$2/bin" ]; then
        mkdir $2/bin
    fi

    if [ ! -e "$2/share/stormscript" ]; then
        mkdir -p $2/share/stormscript
    fi

    cp stormscript $2/bin
    sudo cp ../src/errors.sts $2/share/stormscript
    sudo cp ../src/scripts/update.py $2/share/stormscript
fi