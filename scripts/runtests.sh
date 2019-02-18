#!/bin/bash
cd ..
cmake CMakeLists.txt
make $1
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
cd tests
printf "\n"

B=0
for i in $( ls | grep .sts ); do
    # put the expected output to test
    if [[ $(echo `cat outputs/$i.txt`) = "$(echo `../build/stormscript $i`)" ]]; then
        echo $B: Test Successful
    else
        echo Test $B failed:
        echo expected$'\n'$(echo `cat outputs/$i.txt`)$'\n'got$'\n'$(echo `../build/stormscript $i`)
        exit 1
    fi
    
    B=$(($B+1))
done