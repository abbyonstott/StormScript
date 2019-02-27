# StormScript v0.6.0 "Fig"

## What's new
* StormScript can now read and write to files
* StormScript now has modules, which allow you to run functions from other StormScript files.
* use `randomrange => min, max;` to generate a random integer in range min, max

## What's Fixed
* else and else if statements were broken
* length didn't work when used in function inside args
* while loops would cause the parser to increase the current line to the point where it was outside of the scope.
* Functions run at the end of other functions caused segmentation faults due to failing to parse a semicolon
* Global variables couldn't be declared
* comparisons using subscripts were broken
* length did not change on modification
* `stsvars::glob` was considered to be true by some compilers, causing crash