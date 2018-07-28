@echo off
IF EXIST stscompile/stscomp.cpp (
    cd stscompile
    echo > stscomp.cpp
    cd ..
) ELSE (
    mkdir stscompile
    cd stscompile
    echo > stscomp.cpp
    cd ..
)
@echo on