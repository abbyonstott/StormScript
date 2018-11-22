#!/bin/bash
cmake CMakeLists.txt
make
install stormscript build/stormscript
rm stormscript

for i in $(ls tests); do
    touch tests/outputs/$i.txt
    echo $(build/stormscript tests/$i) > tests/outputs/$i.txt
done