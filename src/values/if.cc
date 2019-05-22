#include "../include/stormscript.h"

void sts::ifs(std::vector<stsvars> vars, int *y) {
    sts getexpr; // TODO: add else and else if
    
    while (expressions[*y].tktype != OPENCURL) {
        getexpr.expressions.push_back(expressions[*y]);
        *y += 1;
    }

    if (toBool(getval(vars, new int(0)).val)) {
        ; // TODO: add new scope method
    }
}