# StormScript v0.3.0 "Cantaloupe"

## What's New
* Modules allow users to run functions from other files. For example, use module `filename.sts` with `mod filename`
* Made `src` dir
* `less`, `greater`, `lesseq`, and `greatereq` operators
* get length of string with `string|length`

## What's Fixed
* Returns could only return variables, changed it to use new getvars function.
* `pop_back()` was run on `prs` causing the vector of the parsed version of the program to lose characters on each loop iteration