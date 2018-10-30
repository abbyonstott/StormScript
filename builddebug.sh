cmake --build build --config Debug --target all -- -j 10
sudo cp build/stormscript /usr/bin
echo StormScript successfully built 
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