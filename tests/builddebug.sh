cd ..
cmake --build build -DCMAKE_CXX_COMPILER=g++ --config Debug --target all -- -j 10
sudo cp build/sts /usr/bin
cd tests
sts example.sts