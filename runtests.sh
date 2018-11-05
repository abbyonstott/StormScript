#!/bin/bash
cmake CMakeLists.txt
make
printf "\n \n \n"

echo Default:
./stormscript

printf "\n"

echo Help:
./stormscript --help

printf "\n"

echo Version:
./stormscript --version

printf "\n"

echo Running tests:

printf "\n"

B=0
for i in $( ls tests ); do
    echo $B: 
    ./stormscript tests/$i
    printf "\n"
    B=$(($B+1))
done

echo $B: File fail test
./stormscript thisfiledoesntexist.sts