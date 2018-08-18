# StormScript

## General

### About

StormScript is an interpreted, object-oriented, scripting language. 

StormScript is based in C++ and is simple to use.

### Basics

StormScript was made on the idea that it is possible to have a strong scripting language that has short, easy to remember syntax.

## The Language

### Files

StormScript files have the extension `.sts`

### Running files

_Once you add the executable to your PATH environment variable:_

* `sts filename.sts`


### Commands

`do`: initial function

`out`: write to console

`in`: take input from console

`str`: make a string variable

`int`: make a integer variable

`func`: make a function

`if`, `else`: if statement

`end`: end current scope

## Examples:

### Hello World Program

```
do{
  out "Hello, World!\n";
}end;
```

### Dealing With Input

```
do{
  in str x;

  if x is "hi"{
    out "you typed hi!\n";
  }else{
    out "You didn't type hi\n";
  }end;
}end;
```

_version specific examples can be found in the `example.sts` file_

Tutorial available [here](https://stormprograms.com/stormscript/helloworld).