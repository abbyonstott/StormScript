#!/bin/bash
cmake CMakeLists.txt -DCMAKE_CXX_COMPILER:STRING="g++"
make
sudo cp stormscript /usr/bin

stormscript finished.sts
exec bash