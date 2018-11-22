#!/bin/bash
cmake CMakeLists.txt
make
install stormscript build/stormscript
rm stormscript
printf "\n \n \n"

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
for i in $( ls tests | grep .sts ); do
    # put the expected output to test
    if [[ $(echo `cat tests/outputs/$i.txt`) = "$(echo `build/stormscript tests/$i`)" ]]; then
        echo $B: Test Successful
    else
        echo Test $B failed:
        echo expected$'\n'$(echo `cat tests/outputs/$i.txt`)$'\n'got$'\n'$(echo `build/stormscript tests/$i`)
        break
    fi
    
    B=$(($B+1))
done