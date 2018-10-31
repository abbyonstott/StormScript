#!/bin/bash
cmake --build build --config Debug --target all -- -j 10
sudo cp build/stormscript /usr/bin
echo StormScript successfully built 