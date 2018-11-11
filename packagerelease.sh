#!/bin/bash
rm -r release/*
cd release
mkdir stormscript_v1.1.1-alpha
cd stormscript_v1.1.1-alpha
mkdir src

cp -r ../../classes src
cp -r ../../stream src
cp -r ../../core src
cp -r ../../values src
cp -r ../../scripts/* .
cp ../../StormScriptconfig.h src
cp -r ../../libraries src

cd ..
tar -cf stormscript_v1.1.1-alpha.tar.xz stormscript_v1.1.1-alpha
