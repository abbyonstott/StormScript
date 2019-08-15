#!/usr/bin/bash
# This is to build and run example.sts on linux using wine
# in order to run this file, you must have your system's 
# wine and mingw-w64 packages

rm -rf ./CMakeFiles
rm -rf CMakeCache.txt
rm Makefile

if [ ! -e /usr/share/stormscript ]; then
	sudo mkdir /usr/share/stormscript
fi

sudo cp ../src/errors.sts /usr/share/stormscript

cmake -DCMAKE_TOOLCHAIN_FILE=mingw32_toolchain.cmake ..
make -j $(nproc)

if [ "$1" = "test" ]; then
	wine stormscript.exe ../example/example.sts
fi