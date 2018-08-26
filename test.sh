#!/bin/bash
#I use this to test updates. Not to be used for production
g++ lang/parse.cpp lang/sts.cpp lang/stsdec.cpp lang/stsstream.cpp -o release/linux-x86/bin/sts
sudo cp release/linux-x86/bin/sts /usr/bin -f
sts example.sts