#!/bin/bash
cmake CMakeLists.txt -DCMAKE_CXX_COMPILER:STRING="g++"
make -j $(nproc)
sudo cp stormscript /usr/bin
sudo cp src/errors.sts /usr/share/stormscript

stormscript finished.sts
exec bash