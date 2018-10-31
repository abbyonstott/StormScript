#!/bin/bash
sh builddebug.sh
printf "\n \n \n"
echo Version:

stormscript --version

printf "\n"

echo Running tests:

printf "\n"

B=0
for i in $( ls tests ); do
    echo $B: 
    stormscript tests/$i
    printf "\n"
    B=$(($B+1))
done

echo $(($B+1)): File fail test
stormscript thisfiledoesntexist.sts