#!/bin/bash
cmake CMakeLists.txt
make
install stormscript build/stormscript
printf "\n \n \n"

echo Default:
build/stormscript

printf "\n"

echo Help:
build/stormscript --help

printf "\n"

echo Version:
build/stormscript --version

printf "\n"

echo Running tests:

printf "\n"

B=0
for i in $( ls tests ); do
    echo $B: 
    build/stormscript tests/$i
    printf "\n"
    B=$(($B+1))
done

echo $B: File fail test
build/stormscript thisfiledoesntexist.sts