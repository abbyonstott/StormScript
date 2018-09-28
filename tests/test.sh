#!/bin/bash
#I use this to test updates. Not to be used for production
g++ ../core/parse.cpp ../core/sts.cpp ../values/stsdec.cpp ../stream/stsstream.cpp ../stream/io.cpp -o ../release/linux-x86/bin/sts
sudo cp ../release/linux-x86/bin/sts /usr/bin -f
sts example.sts