#!/bin/bash
cmake CMakeLists.txt
make
sudo cp stormscript /usr/bin
g++ src/libraries/system/reader.cc -o src/libraries/system/system.stslib 
if [ ! -e ~/.stormscript ]; then
    mkdir ~/.stormscript
    echo 'export PATH=$PATH:'$HOME'/.stormscript' >> ~/.bashrc
fi
cp src/libraries/*/*.stslib ~/.stormscript
cp src/libraries/*/*.py ~/.stormscript
cp -r src/libraries/system/stormscript ~/.stormscript
stormscript finished.sts
exec bash