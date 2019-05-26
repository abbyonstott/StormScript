# StormScript 1.0.0

## What's New
* Use the `$` symbol followed by a variable name inside of a string literal to concatenate that variable into the string
* Use `stormscript test filename` to run a live interpretation of filename.sts 
* `for INT` runs a for loop starting at 0 and ending on INT
* `foreach PLACEHOLDER in (list/str)` runs through every item in a list or string 
* `do` is no longer required
* rewrote interpreter to use switch statements
* using enumerations to determine statements rather than string literal
* functions can be declared in any scope

## What's Fixed
* Removed snapcraft files
* Variables can be used in the filenames in the `read` and `write` commands
* StormScript doesn't mess up when if statements are nested
* boolean variables and literals now work in `if` statements
* Comparisons always work out to booleans, meaning that they are now interchangeable