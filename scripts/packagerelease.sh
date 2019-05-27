#!/bin/bash
cd ..
rm -r release/*
echo "What is the version number (Formatted M.m.p):"
read vnum

echo "Packaging stormscript v$vnum for release."

cmake CMakeLists.txt -DCMAKE_CXX_COMPILER:STRING="g++"
make -j $(nproc)
sudo mv stormscript /usr/bin/stormscript

if [ ! -e /usr/share/stormscript ]; then
    sudo mkdir /usr/share/stormscript
fi;

sudo mv src/core/errors.sts /usr/share/stormscript

exec bash

printf "\n"

echo Running tests:
cd tests
printf "\n"

B=0
for i in $( ls | grep .sts ); do
    # put the expected output to test
    if [[ $(echo `cat outputs/$i.txt`) = "$(echo `stormscript $i`)" ]]; then
        echo $B: Test Successful
    else
        echo Test $B failed:
        echo expected$'\n'$(echo `cat outputs/$i.txt`)$'\n'got$'\n'$(echo `stormscript $i`)
        echo "Failed to package stormscript v$vnum"
        exit 1
    fi
    
    B=$(($B+1))
done

cd ..

echo "Moving files from src to release/stormscript_v$vnum"

cd release

mkdir stormscript_v$vnum
cd stormscript_v$vnum

cp ../../CMakeLists.txt .
cp -r ../../src .
cp ../../build-scripts/* .

echo "Compressing folder stormscript_v$vnum."
cd ..
tar -cf stormscript_v$vnum.tar.xz stormscript_v$vnum

echo "Successfully packaged stormscript_v$vnum.tar.xz"