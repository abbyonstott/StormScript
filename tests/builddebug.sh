cd ..
cmake --build build --config Debug --target all -- -j 10
sudo cp build/sts /usr/bin
cd tests
echo StormScript successfully built