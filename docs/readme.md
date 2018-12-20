# About

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
func f => str x {
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