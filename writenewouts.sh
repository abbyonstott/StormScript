#!/bin/bash
cmake CMakeLists.txt
make
install stormscript build/stormscript
rm stormscript

cd tests

for i in $(ls); do
    touch outputs/$i.txt
    echo $(../build/stormscript $i) > outputs/$i.txt
done