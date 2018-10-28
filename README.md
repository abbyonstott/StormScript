# StormScript
[![Snap Status](https://build.snapcraft.io/badge/stormprograms/StormScript.svg)](https://build.snapcraft.io/user/stormprograms/StormScript)

This is the GitHub repository for the StormScript Scripting language

## Layout

Folder | Description | Contents 
------ | ----------- | --------
/ | | `files.json`: A JSON file with the paths to the stormscript standard files.
docs/ | contributing guide, code of conduct. etc. | `CODE_OF_CONDUCT.md`: code of conduct. `CONTRIBUTING.md`: contributing guide.
core/ | The core StormScript files | `sts.cpp`: file input, reading, errors. `parse.cpp`: The parser and interpreter. `stsclasses.h`: all classes needed for StormScript development.
stream/ | Files that deal with the console. | `stsstream.cpp`: if statements and `sys`. `io.cpp`: `print` and `in` commands
classes/ | Files that deal with classes. | `dectype.cpp`: class declaration 
values/ | Files that deal with variables and functions. | `stsdec.cpp`: Lets you declare variables. `man.cpp`: lets you manipulate variables  
tests/ | Files that allow you to test StormScript | `test.py`: compiles stormscript and runs `example.sts`. `example.sts`: The file where features are tested. There are also various other tests
