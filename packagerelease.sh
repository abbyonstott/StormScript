#!/bin/bash
rm -r release/*
cd release
mkdir stormscript_v0.3.1
cd stormscript_v0.3.1

cp ../../CMakeLists.txt .
cp -r ../../src .
cp -r ../../api .
cp ../../build-scripts/* .

cd ..
tar -cf stormscript_v0.3.0.tar.xz stormscript_v0.3.1
