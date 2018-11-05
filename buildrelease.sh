#!/bin/bash
rm -r release/*

mkdir release/src

cp -r classes release/src
cp -r stream release/src
cp -r core release/src
cp -r values release/src
cp -r scripts/* release
cp StormScriptconfig.h release/src
cp -r libraries release/src

cd release

cmake  CMakeLists.txt
make