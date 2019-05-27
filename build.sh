#!/bin/bash
cmake .
make -j $(nproc)
if [ ! -e /usr/share/stormscript ]; then
    sudo mkdir /usr/share/stormscript
fi
sudo mv stormscript /usr/bin/stormscript

sudo cp src/core/errors.sts /usr/share/stormscript
sudo chmod u+x /usr/share/stormscript/errors.sts
