cmake --build build --config Debug --target all -- -j 10
sudo cp build/stormscript /usr/bin
echo StormScript successfully built 
printf "\n \n \n"
echo Running tests
for i in $( ls tests ); do
    stormscript tests/$i
done