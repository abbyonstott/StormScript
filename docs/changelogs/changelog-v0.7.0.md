# StormScript v0.7.0 "Grape"

## What's New
* Mac install script
* Class constructors with the `def` keyword
* errors moved to `errors.sts` from `core/errors.cc`
* you can now modify specific characters in a string or specific characters in a list using subscripts
* use `stormscript install modname` to install official module by name of modname
* define a function and declare it later with forward declaration

## What's Fixed
* Version would only show at top if StormScript was running from PATH
* Print function would crash when printing lists with subscripts
* fixed issue with chains of else if blocks causing the parser to go over the number of objects in program vector
* Parser no longer keeps whitespace