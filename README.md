# StormScript
[![Snap Status](https://build.snapcraft.io/badge/stormprograms/StormScript.svg)](https://build.snapcraft.io/user/stormprograms/StormScript)

This is the GitHub repository for the StormScript Scripting language

## Layout

Folder | Description
------ | -----------
docs/ | contributing guide, code of conduct. etc.
core/ | The core StormScript files
stream/ | Files that deal with the console.
scripts/ | Scripts to be packaged with releases
classes/ | Files that deal with classes.
values/ | Files that deal with variables and functions.
tests/ | Files that allow you to test StormScript

## Files you should know

file | Description
---- | -----------
core/stsclasses.h | This is where all classes needed for a program to run are put.
core/sts.cpp | This is where files are read.
core/errors.cpp | This is where all new errors are added.
core/parse.cpp | This is the parser and the interpreter.
