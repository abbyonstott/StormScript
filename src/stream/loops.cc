#include "../include/stormscript.h"

void whileloop(sts *script, std::vector<stsvars> *variables, std::vector<stsfunc> functions, int *y) {
    *y += 1;
    int n = *y;
    script->looping = true;

    while (toBool(script->getval(variables, functions, &n).val)) {
        script->newScope(new int(n), variables, &functions);

        if (!script->looping) break;

        n = *y; // set n back to y to repeat
    }

    while (script->expressions[*y].tktype != OPENCURL) *y += 1;
    *y += 1;

    script->looping = false;
    scopedown(y, script->expressions);
}


void forloop(sts *script, std::vector<stsvars> *variables, std::vector<stsfunc> functions, int *y) {
    *y += 1;
    bool foreach = (script->expressions[*y+1].btn == STSIN);
    script->looping = true;

    if (foreach) {
        stsvars root;
        string name;
        int rootsize;
        name = script->expressions[*y].contents;
        
        *y += 2;

        root = findVar(*variables, script->expressions[*y].contents); // grab variable listed on 3rd argument of for loop
        *y += 1;

        switch (root.type) {
            case 's':
            case 'l': rootsize = root.length;
                break;
            case 'i':
            case 'b':
                script->error(9, root.name);
        }

        for (int i = 0; i < rootsize; i++) {
            std::vector<stsvars> newvars = *variables;
            stsvars placeholder;

            if (root.type == 'l')
                placeholder = root.vals[i];
            else {
                placeholder.val = std::to_string(root.val[i]);
                placeholder.length = 1;
                placeholder.type = 's';
            }
            placeholder.name = name;

            newvars.push_back(placeholder);

            script->newScope(new int(*y), &newvars, &functions);

            if (!script->looping) break;
        }

        *y += 1;

    }
    else {
        int r = std::stoi(script->getval(variables, functions, y).val);
        *y += 1;
        
        if (r <= 0)
            script->error(17, std::to_string(r));

        for (int i = 0; i < r; i++) {
            script->newScope(new int(*y), variables, &functions);   
            if (!script->looping) break;
        }

        *y += 1;
    }

    script->looping = false;
    scopedown(y, script->expressions);
}
