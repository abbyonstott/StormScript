# What's here?

These files make up the StormScript standard library. 

They contain the following:

## sts.cpp:

* Reads files and returns a vector called `prg` that contains the lines
* Has an `error()` function that will return errors and terminate the program
* Takes in command line args to read a specific file

## parse.cpp
* This file contains the parser and the interpreter
* The function `parse()` takes in the value of the `prg` vector and splits it up by various characters and returns a value called `prs` for the interpreter to use
* The function `interp()` takes the value of `prs` and performs various actions based on what the value of `prs` is

## stsdec.cpp
* stsdec.cpp contains the functions that allow you to declare functions and variables
* it uses the classes `stsvars` to make variables
* the function `declare()` is for variables

## stsstream.cpp
* this file contains streams for specific values
* the function `out()` takes the line number and the current variables to print to the console when the function `interp()` finds the `out` statement in a parsed file
* the function `in()` takes the line number to determine which variables it is taking in and returns a `stsvars` type
* the function `compare()` is for if statements. It reads through the values of the current variables to find the one it is comparing and then compares it
* the function `sys()` executes system commands

## stsclasses.h
* this file contains the various classes that the StormScript lanuage uses