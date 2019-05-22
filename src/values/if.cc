#include "../include/stormscript.h"

void sts::ifs(std::vector<stsvars> vars, int *y) {
    /*
    if statements are pretty easy to parse as they are always formated like this
    BUILTIN |    VALUE/COMPARISON*    |   TOKEN
    --------|-------------------------|-----------
       if   |          var            |    {
    
    *The VALUE/EXPRESSION can be a bool literal, a variable, or a comparison. This is not determined here, but later in getval()
    */

    sts getexpr; // TODO: add else if
    *y += 1;
    
    while (expressions[*y].tktype != OPENCURL) {
        getexpr.expressions.push_back(expressions[*y]);
        *y += 1;
    }

    getexpr.expressions.push_back(expressions[*y]);

    if (toBool(getexpr.getval(vars, new int(0)).val)) { // run if statement is true
        newScope(y, vars);
        *y += 1; // get out of scope to check for else
    }
    else { // otherwise run else
        *y += 1;
        scopedown(y, expressions); // scope down to else

        if (expressions[*y].btn == ELSE) {
            *y += 1;
            newScope(y, vars); // run else statement
        }
    }

    if (expressions[*y].btn == ELSE) {
        *y += 2;
        scopedown(y, expressions);
    }
}