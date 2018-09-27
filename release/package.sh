#!/bin/bash
# this builds stormscript for linux and windows.
g++ ../core/parse.cpp ../core/sts.cpp ../values/stsdec.cpp ../stream/stsstream.cpp -o linux-x86/bin/sts
g++ ../libraries/helloworldpy/helloworldpy.cpp -o linux-x86/libs/helloworldpy.stslib
g++ ../libraries/helloworldlib/helloworld.cpp -o linux-x86/libs/helloworld.stslib
tar -czvf release/linux-x86_64.tar.gz release/linux-x86
x86_64-w64-mingw32-g++ ../core/parse.cpp ../core/sts.cpp ../values/stsdec.cpp ../stream/stsstream.cpp -o release/windows-x86/bin/sts.exe -static-libgcc -static-libstdc++
x86_64-w64-mingw32-g++ ../libraries/helloworldpy/helloworldpy.cpp -o release/windows-x86/bin/helloworldpystslib.exe -static-libgcc -static-libstdc++
x86_64-w64-mingw32-g++ ../libraries/helloworldlib/helloworld.cpp -o release/windows-x86/bin/helloworldstslib.exe -static-libgcc -static-libstdc++
zip -r windows-x86_64.zip windows-x86