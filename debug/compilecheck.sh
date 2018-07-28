#!/bin/bash
if [ -e stscompile/stscomp.cpp ]
then 
    cd stscompile
    touch stscomp.cpp
    cd ..
else 
    mkdir stscompile
    cd stscompile
    touch stscomp.cpp
    cd ..
fi