#!/bin/bash
cmake CMakeLists.txt
make
sudo cp stormscript /usr/bin
stormscript finished.sts