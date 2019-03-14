brew install cmake
cmake .
make
touch ~/.profile
echo "export PATH="`pwd`":\$PATH" >> ~/.profile
source ~/.profile
