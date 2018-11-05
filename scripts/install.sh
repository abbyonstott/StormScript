#!/bin/bash
cmake CMakeLists.txt
make
sudo cp stormscript /usr/bin
mkdir ~/.stormscript
cp src/libraries/*/*.stslib ~/.stormscript
cp src/libraries/*/*.py ~/.stormscript
echo 'export PATH=$PATH:'$HOME'/.stormscript' >> ~/.bashrc
stormscript finished.sts