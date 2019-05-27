#!/bin/bash
cd ..
cmake CMakeLists.txt
make -j $(nproc)
install stormscript build/stormscript
rm stormscript

cd tests

rm -r outputs/*

for i in $(ls | grep .sts); do
    touch outputs/$i.txt
    echo $(../build/stormscript $i) > outputs/$i.txt
done