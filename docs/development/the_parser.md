# The Parser

## Evaluation

One of the main files in stormscript is the file [eval.cc](/src/interpreter/eval.cc). `eval.cc` is run directly after the file [parse.cc](/src/parser/parse.cc).

Expressions are "sorted" into 5 different enumerations:

`BUILTIN`: Built in functions

`VALUE`: Any literal

`UNKNOWN`: Could be an error, or user defined variables, functions, or classes

`TOKEN`: Any symbol that isn't a semicolon

`ENDEXPR`: A semicolon

## Characters that are left out

Needless to say, whitespace and empty newlines are left out of the parsed program as they serve no purpose to the actual execution of the program.

Less obviously, parentheses are completely left out of the program (for now) because they currently would only change the look of the program