#!/bin/bash
cmake CMakeLists.txt -DCMAKE_CXX_COMPILER:STRING="g++"
make -j $(nproc)


# build only arg does not install
if [ ! "$1" = "--prefix" ]; then
    echo "Expected prefix argument."
    exit 1;
else 
    if [ ! -e "/usr/share/stormscript" ]; then
        mkdir $2/share/stormscript
    fi

    cp stormscript $2/bin
    cp src/errors.sts $2/share/stormscript
    cp src/scripts/update.py $2/share/stormscript
fi

$2/stormscript finished.sts