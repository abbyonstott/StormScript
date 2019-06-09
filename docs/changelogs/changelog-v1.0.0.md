# StormScript v1.0.0

## What's New
* Use the `$` symbol followed by a variable name inside of a string literal to concatenate that variable into the string
* `for INT` runs a for loop starting at 0 and ending on INT
* `do` is no longer required
* rewrote interpreter to use switch statements
* using enumerations to determine statements rather than string literal
* functions can be declared in any scope
* moved errors.sts from /usr/bin to /usr/share/stormscript
* Function arguments no longer require you to specify the name
* `for PLACEHOLDER in LIST/STR` creates a foreach loop
* `randomrange and rand` now uses Mersenne Twister generation rather than cpp  `rand()` function
* added `break` for loops
* errors are now parsed before runtime

## What's Fixed
* Removed snapcraft files
* Variables can be used in the filenames in the `read` and `write` commands
* StormScript doesn't mess up when if statements are nested
* boolean variables and literals now work in `if` statements
* Comparisons always work out to booleans, meaning that they are now interchangeable
* Random no longer generates integers outside of range
* Scoped variable inheritance now works, so variables defined inside of a scope are accessible to the scope and any child scopes
* Install script now uses all available processor cores
* packagerelease.sh now installs stormscript to run tests

# Beta 2

## What's fixed
* Concatenation would break if there was no space at the end of value
* `in` would always give error with name variable
* `+:` operator now works
* Fixed for loop running `getvals()` with `new int(*y)`, causing the interpreter to be off