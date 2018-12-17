#!/bin/bash
rm -r release/*
cd release
mkdir stormscript_v0.4.0
cd stormscript_v0.4.0

cp ../../CMakeLists.txt .
cp -r ../../src .
cp -r ../../api .
cp ../../build-scripts/* .

cd ..
tar -cf stormscript_v0.4.0.tar.xz stormscript_v0.4.0
