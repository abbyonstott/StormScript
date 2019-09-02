#!/bin/bash

rm -rf ./CMakeFiles
rm -rf CMakeCache.txt
rm Makefile

cmake ..
make -j $(nproc)
if [ ! -e /usr/share/stormscript ]; then
    sudo mkdir /usr/share/stormscript
fi
sudo mv stormscript /usr/bin/stormscript

sudo cp ../src/errors.sts /usr/share/stormscript
sudo cp ../src/scripts/update.py /usr/share/stormscript
sudo chmod u+x /usr/share/stormscript/errors.sts
