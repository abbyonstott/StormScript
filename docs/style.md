# Style

## Table of Contents

* [Info](#info)
* [C++ Style](#c++-ctyle)
* [Python Style](#python-style)
* [StormScript Style](#stormscript-style)

# Info
I mainly created this code as a guide and less of a "law" because I feel that it is important to have readable code, but not to stress it so much as to deter newcomers. I sometimes will forget to follow this style guide, and if you do as long as your code is readable I will accept it. That said, I want you to try to use this style guide as much as you can for the sake of time. If I forget to follow this somewhere, feel free to create a PR that cleans up my code.

# C++ Style
C++ has the strictest rules when it comes to styling as it makes up the majority of the project.

## Includes
**YOU MUST FOLLOW THIS**

All includes must go at the top of [stsclasses.h](/core/stsclasses.h).

## Formatting
The general rule of formatting here is not to use more lines than you need to make it readable.

## Braces
Don't use braces for one line scopes.
```cpp
for (int i = 0; i<=number; i++)
    // do something
```
rather than
```cpp
for (int i = 0; i<=number; i++) {
    // do something
}
```

If you are using multiple lines in your scope, always include braces.

```cpp
for (int i = 0; i<=number; i++) {
    cout << "Hi there.\n";
    foo(bar);
}
```
rather than
```cpp
for (int i = 0; i<=number; i++)
    cout << "Hi there.\n";
    foo(bar);
```
**Always put braces on the same line as the statement with a space separating them**

## SubScripts

Use `string::back()` and `string::front()` when applicable

for instance
```cpp
if  ((prs[y].back()==':') || (prs[y+4]==":")) {
    ...
}
```
source: [man.cpp](/values/man.cpp)


## Keywords
Use `'\n'` instead of `std::endl;` unless absolutely neccessary