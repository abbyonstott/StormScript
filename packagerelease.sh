#!/bin/bash
rm -r release/*
cd release
mkdir stormscript_v0.1.0
cd stormscript_v0.1.0
mkdir src

cp -r ../../classes src
cp -r ../../stream src
cp -r ../../core src
cp -r ../../values src
cp -r ../../scripts/* .
cp ../../StormScriptconfig.h src
cp -r ../../libraries src

cd ..
tar -cf stormscript_v0.1.0.tar.xz stormscript_v0.1.0
