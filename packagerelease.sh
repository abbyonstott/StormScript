#!/bin/bash
rm -r release/*
cd release
mkdir stormscript_v0.3.0
cd stormscript_v0.3.0
mkdir src

cp ../../CMakeLists.txt src
cp -r ../../api src
cp -r ../../interpreter src
cp -r ../../parser src
cp -r ../../classes src
cp -r ../../stream src
cp -r ../../core src
cp -r ../../values src
cp -r ../../scripts/* .
cp ../../StormScriptconfig.h src
cp -r ../../libraries src

cd ..
tar -cf stormscript_v0.3.0.tar.xz stormscript_v0.3.0
