#!/bin/bash
cmake CMakeLists.txt -DCMAKE_CXX_COMPILER:STRING="g++"
make
sudo cp stormscript /usr/bin
sudo cp src/core/errors.sts /usr/share/stormscript

stormscript finished.sts
exec bash