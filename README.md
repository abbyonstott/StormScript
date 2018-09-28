# StormScript

This is the GitHub repository for the StormScript Scripting language

## Layout

Folder | Description | Contents 
------ | ----------- | --------
/ | | `files.json`: A JSON file with the paths to the stormscript standard files.
docs/ | contributing guide, code of conduct. etc. | `CODE_OF_CONDUCT.md`: code of conduct. `CONTRIBUTING.md`: contributing guide.
core/ | The core StormScript files | `sts.cpp`: file input, reading, errors. `parse.cpp`: The parser and interpreter. `stsclasses.h`: all classes needed for StormScript development.
stream/ | Files that deal with the console. | `stsstream.cpp`: if statements and `sys`. `io.cpp`: `print` and `in` commands
values/ | Files that deal with variables and functions. | `stsdec.cpp`: Lets you declare variables.
libraries/ | StormScript test libraries. | This folder contains three test libraries that all print `Hello, world!`. 
tests/ | Files that allow you to test StormScript | `test.sh`: compiles stormscript and runs `example.sts`. `example.sts`: The file where features are tested.
release/ | Compiled versions of libraries | `package.sh`: shell script that compiles StormScript and its libraries for Linux and Windows and compresses the folders for release. `package.py`: Python file that parses paths and sends it to `package.sh`