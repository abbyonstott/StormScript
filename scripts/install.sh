#!/bin/bash
cmake src/CMakeLists.txt
make -C src
sudo cp src/stormscript /usr/bin
g++ src/libraries/system/reader.cc -o src/libraries/system/system.stslib 
g++ src/libraries/random/reader.cc -o src/libraries/random/random.stslib 
if [ ! -e ~/.stormscript ]; then
    mkdir ~/.stormscript
    echo 'export PATH=$PATH:'$HOME'/.stormscript' >> ~/.bashrc
fi
cp src/libraries/*/*.stslib ~/.stormscript
cp src/libraries/*/*.py ~/.stormscript
cp -r src/api/python/stormscript ~/.stormscript
stormscript finished.sts
exec bash