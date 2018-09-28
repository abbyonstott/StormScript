#!/bin/bash
# this builds stormscript for linux and windows.
g++`./package.py`-o linux-x86/bin/sts
g++ ../libraries/helloworldpy/helloworldpy.cpp -o linux-x86/libs/helloworldpy.stslib
g++ ../libraries/helloworldlib/helloworld.cpp -o linux-x86/libs/helloworld.stslib
tar -czvf linux-x86_64.tar.gz linux-x86
x86_64-w64-mingw32-g++`./package.py`-o windows-x86/bin/sts.exe -static-libgcc -static-libstdc++
x86_64-w64-mingw32-g++ ../libraries/helloworldpy/helloworldpy.cpp -o windows-x86/bin/helloworldpystslib.exe -static-libgcc -static-libstdc++
x86_64-w64-mingw32-g++ ../libraries/helloworldlib/helloworld.cpp -o windows-x86/bin/helloworldstslib.exe -static-libgcc -static-libstdc++
zip -r windows-x86_64.zip windows-x86