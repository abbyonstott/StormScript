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

## What's Fixed
* Removed snapcraft files
* Variables can be used in the filenames in the `read` and `write` commands
* StormScript doesn't mess up when if statements are nested
* boolean variables and literals now work in `if` statements
* Comparisons always work out to booleans, meaning that they are now interchangeable
* Random no longer generates integers outside of range
* Scoped variable inheritance now works, so variables defined inside of a scope are accessible to the scope and any child scopes
* Install script now uses all available processor cores

# Beta 1

## What's changed
* Removed `type`: Will be added back later
* Removed modules: Will be added back later