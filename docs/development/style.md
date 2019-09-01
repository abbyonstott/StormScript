# Style

## Table of Contents

* [Info](#info)
* [Commenting](#commenting)
* [C++ Style](#c++-style)
* [StormScript Style](#stormscript-style)

# Info
I mainly created this code as a guide and less of a "law" because I feel that it is important to have readable code, but not to stress it so much as to deter newcomers. I sometimes will forget to follow this style guide, and if you do as long as your code is readable I will accept it. That said, I want you to try to use this style guide as much as you can for the sake of time. If I forget to follow this somewhere, feel free to create a PR that cleans up my code.

# Commenting

This should go without saying, but please comment on your code. I love reading code, but I also want to know what it does. ;)

# C++ Style
C++ has the strictest rules when it comes to styling as it makes up the majority of the project.

## Indention
Use the `\t` character

## Includes
**YOU MUST FOLLOW THIS**

All includes must go at the top of [includes.h](/src/include/includes.h).

All C++ source files must include src/include/stormscript.h

## Scopes

If a scope only contains 1 line of code, put it on the same line as the condition that creates it without curly brackets

For example:

```cpp
if (expressions[*y].t == ENDEXPR) *y += 1;
```
or
```cpp
if (expressions[*y].t == ENDEXPR)
	*y += 1;
```

Otherwise, curly braces go 1 space in front of scope defining statement.

```cpp
switch (expressions[*y].t) {
        ...
}
```


## If statements and Switches

If you are dealing with enumerations, integers, or characters, you should use switch statements otherwise use if statements.

# StormScript Style

## Parentheses

Parentheses in StormScript are completely optional. However, in this project, please use parentheses around conditional operators