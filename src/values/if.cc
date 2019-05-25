#include "../include/stormscript.h"

void sts::ifs(std::vector<stsvars> vars, std::vector<stsfunc> functions, int *y) {
    /*
    if statements are pretty easy to parse as they are always formated like this
    BUILTIN |    VALUE/COMPARISON*    |   TOKEN
    --------|-------------------------|-----------
       if   |          var            |    {
    
    *The VALUE/EXPRESSION can be a bool literal, a variable, or a comparison. This is not determined here, but later in getval()
    */

    sts getexpr;
    *y += 1;
    
    while (expressions[*y].tktype != OPENCURL) {
        getexpr.expressions.push_back(expressions[*y]);
        *y += 1;
    }

    getexpr.expressions.push_back(expressions[*y]);
    bool expr = toBool(getexpr.getval(vars, new int(0)).val);

    if (expr) {
        newScope(y, vars, {});
        *y += 1; // get out of scope to check for else
    }
    else { 
        *y += 1;
        scopedown(y, expressions);

        if (expressions[*y+1].btn == ELSE) {
            /* 
            This works because it parses the expression after else. 
            This would be { or OPENCURL if it is a standard else statement and IF it it were an else if statement.
            */
            *y += 1;
            newScope(y, vars, {});
        }
    }

    if (expressions[*y].btn == ELSE) {
        *y += 2;
        scopedown(y, expressions);
    }
    else if (expr) // subtract one if expression is false to compensate for next line of program
        *y -= 1;
}