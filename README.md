![](images/logo.png)

[![GitHub license](https://img.shields.io/github/license/stormprograms/stormscript.svg)](https://github.com/stormprograms/StormScript/blob/master/LICENSE)
![GitHub (pre-)release](https://img.shields.io/github/release-pre/stormprograms/stormscript.svg)
![GitHub All Releases](https://img.shields.io/github/downloads/stormprograms/stormscript/total.svg)
![GitHub repo size in bytes](https://img.shields.io/github/repo-size/stormprograms/stormscript.svg)

[![Get it from the Snap Store](https://snapcraft.io/static/images/badges/en/snap-store-black.svg)](https://snapcraft.io/stormscript)

## Table of Contents
* [Why is this special?](#why-is-this-special)
* [How to Build](#how-to-build)
* [Layout](#layout)
* [Files You Should Know](#files-you-should-know)

## Why is this special?

StormScript is important not because it presents 1 or 2 revolutionary ideas that change your usual workflow, but because it changes almost everything about common programming syntax to make it easier to read and write. **This may seem more like a problem at first,** but I believe that StormScript changes programming syntax *for the better.* Here are a few examples:
1. Keywords
For most people, keywords make no sense when learning programming languages, and a large portion of what StormScript changes has to do with keywords.
In most languages in order to declare custom types, you would use the `class` keyword. The word class kind of has a connection with the word type, but at that point why not just use the word `type`. This is something StormScript addresses.
```
type person{
  int age;
  str name;
  bool gender;
}
```
In StormScript the keyword `do` replaces the `main` function.

2. Symbols
StormScript's second major difference is in symbols. Symbols are almost, if not as important as keywords in programming. In StormScript, this is just as true as in any other language. The largest change with symbols in StormScript is in meaning. An example is the `=>` symbol, which in most programming language means *define.* In StormScript, `=>` means *with.* In a function with arguments, you would put the `=>` symbol followed by the arguments.
```
@args: str x;
func f{
  printl x;
}

do{
  f => x: "hi";
}
```
Another example of this is the `|` symbol, which is usually used as a separator. In StormScript, the `|` symbol tells the intepreter to find a property. For example:

```
type person{
  int age;
  str name;
  bool gender;
}

do{
  person p;
  p|name: "Bob";
  p|age: 24;
  p|gender: true;
  
  str name: p|name;
  
  printl name;
}

```
In  StormScript, the `is` keyword replaces the `==` symbol and `not` replaces the `!=` symbol.

3. API
Possible the most important part of StormScript is the API. Generally, in order to create a library in a language, you have to develop it in that language. In StormScript, libraries can be made in Python, StormScript, and C++.

## How to Build

Terminal:

To build StormScript clone this repository and cd into it. Run 
```
$ cmake CMakeLists.txt
```
and
```
$ make
```
You can then add it to path or install it to /usr/bin.

Visual Studio Code:

Clone this repository like before and open it in Visual Studio Code. Make sure you have the CMake, C++, and python plugins installed. Press `Build:` in the bottom left or press `f5` to start debugging.

When it builds, it should be put into a `build/` directory.

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

## Files You Should Know

file | Description
---- | -----------
[core/stsclasses.h](core/stsclasses.h) | This is where all classes needed for a program to run are put.
[core/stormscript.cpp](core/stormscript.cpp) | This is where files are read.
[core/errors.cpp](core/errors.cpp) | This is where all new errors are added.
[parser/parse.cpp](parser/parse.cpp) | This is the parser.
[interpreter/exec.cpp](interpreter/exec.cpp) | This is the function that interprets functions
