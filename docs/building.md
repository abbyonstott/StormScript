# Building StormScript

Make a directory called build

**You must have gcc-8/g++-8 installed (MinGW for Windows) and CMake**

GDB is also highly recommended for debugging

## Linux

Terminal:
```sh
cd build
./build.sh --prefix /DIRECTORY
```

Set prefix to /usr to add to PATH

## Windows

Make sure you have MinGW and CMake installed (in PATH)
run `cmake -G "MinGW Makefiles"`
then run `mingw32-make`

also make sure that you have src/core in PATH for errors to work

## Visual Studio Code

Press `Build:` in the bottom left or press `f5` to start debugging (if GDB is installed).

When it builds, it should be put into a `build/` directory.

if you are on windows, use the debug profile "(gdb) launch on windows"