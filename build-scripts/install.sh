#!/bin/bash
cmake CMakeLists.txt -DCMAKE_CXX_COMPILER:STRING="g++"
make -j $(nproc)
sudo cp stormscript /usr/bin
sudo cp src/errors.sts /usr/share/stormscript


# build only arg does not install
if [ ! "$1" = "buildonly" ]; then
    if [ ! -e "/usr/share/stormscript" ]; then
        sudo mkdir /usr/share/stormscript
    fi

    sudo cp stormscript /usr/bin
    sudo cp src/errors.sts /usr/share/stormscript
    sudo cp src/scripts/update.py /usr/share/stormscript
fi

stormscript finished.sts