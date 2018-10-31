#!/bin/bash
cmake CMakeLists.txt
make
sudo cp stormscript /usr/bin
echo StormScript successfully built
