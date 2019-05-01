# Building StormScript

Make a directory called build

You must have gcc installed (MinGW for Windows) and CMake

## Linux

Terminal:
`sh build.sh`


## Windows

Make sure you have MinGW-make installed

Run CMake GUI, and configure for MinGW-make

output should be a MakeFile, run mingw-make in that directory.


## Visual Studio Code

Clone this repository like before and open it in Visual Studio Code. Make sure you have the CMake, C++, and python plugins installed. Press `Build:` in the bottom left or press `f5` to start debugging.

When it builds, it should be put into a `build/` directory.
