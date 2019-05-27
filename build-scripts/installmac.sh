brew install cmake
cmake .
make -j $(nproc)
cp src/core/errors.sts .
touch ~/.profile
echo "export PATH="`pwd`":\$PATH" >> ~/.profile
source ~/.profile
