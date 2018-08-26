#!/bin/bash
g++ library/webpysts.cpp -o library/webpysts.stslib
cd test/
sts webpytest.sts
cd ../..