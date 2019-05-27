#include "../include/stormscript.h"

void whileloop(sts *script, std::vector<stsvars> *variables, std::vector<stsfunc> functions, int *y) {
    *y += 1;
    int n = *y;

    while (condition(script, &n, variables, functions)) {
        script->newScope(new int(n), variables, &functions);
        n = *y; // set n back to y to repeat
    }

    while (script->expressions[*y].tktype != OPENCURL) *y += 1;
    *y += 1;
    scopedown(y, script->expressions);
}


void forloop(sts *script, std::vector<stsvars> *variables, std::vector<stsfunc> functions, int *y) {
    *y += 1;
    int r = std::stoi(script->getval(variables, functions, new int(*y)).val);
    *y += 1;

    if (r <= 0)
        script->error(17, std::to_string(r));

    for (int i = 0; i < r; i++) {
        script->newScope(new int(*y), variables, &functions);   
    }

    *y += 1;

    scopedown(y, script->expressions);
}