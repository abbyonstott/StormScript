#!/bin/bash
# this builds stormscript for linux and windows.
g++ lang/parse.cpp lang/sts.cpp lang/stsdec.cpp lang/stsstream.cpp -o release/linux-x86/bin/sts
g++ libraries/helloworldpy/helloworldpy.cpp -o release/linux-x86/libs/helloworldpy.stslib
g++ libraries/helloworldlib/helloworld.cpp -o release/linux-x86/libs/helloworld.stslib
tar -czvf release/linux-x86_64.tar.gz release/linux-x86
x86_64-w64-mingw32-g++ lang/parse.cpp lang/sts.cpp lang/stsdec.cpp lang/stsstream.cpp -o release/windows-x86/bin/sts.exe -static-libgcc -static-libstdc++
x86_64-w64-mingw32-g++ libraries/helloworldpy/helloworldpy.cpp -o release/windows-x86/libs/helloworldpystslib.exe -static-libgcc -static-libstdc++
x86_64-w64-mingw32-g++ libraries/helloworldlib/helloworld.cpp -o release/windows-x86/libs/helloworldstslib.exe -static-libgcc -static-libstdc++
zip -r release/windows-x86_64.zip release/windows-x86