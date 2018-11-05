# StormScript Python API

## What is this?
The StormScript Python API allows you to create libraries for StormScript in Python.

File | Contents
-----|-------
stormscript/ | This is the python module for the API
getname.py | This file grabs the name of the library, which should be specified as an argument to `stormscript -l`.
reader.cc | This C++ file encodes the command and variable data it recieves into JSON.
