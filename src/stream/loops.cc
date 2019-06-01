#include "../include/stormscript.h"

void whileloop(sts *script, std::vector<stsvars> *variables, std::vector<stsfunc> functions, int *y) {
    *y += 1;
    sts s = *script;
    int n = *y;
    s.looping = true;

    while (toBool(s.getval(variables, functions, &n).val)) {
        s.newScope(new int(n), variables, &functions);

        if (!s.looping) break;

        n = *y; // set n back to y to repeat
    }

    while (s.expressions[*y].tktype != OPENCURL) *y += 1;
    *y += 1;

    s.looping = false;
    scopedown(y, s.expressions);
}


void forloop(sts *script, std::vector<stsvars> *variables, std::vector<stsfunc> functions, int *y) {
    *y += 1;
    sts s = *script;
    bool foreach = (s.expressions[*y+1].btn == STSIN);
    s.looping = true;

    if (foreach) {
        stsvars root;
        string name;
        int rootsize;
        name = s.expressions[*y].contents;
        
        *y += 2;

        root = findVar(*variables, s.expressions[*y].contents); // grab variable listed on 3rd argument of for loop
        *y += 1;

        switch (root.type) {
            case 's':
            case 'l': rootsize = root.length;
                break;
            case 'i':
            case 'b':
                s.error(9, root.name);
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

            s.newScope(new int(*y), &newvars, &functions);

            variables->insert(variables->begin(), newvars.begin(), newvars.end()-1);

            if (!s.looping) break;
        }

        *y += 1;

    }
    else {
        int r = std::stoi(s.getval(variables, functions, y).val);
        *y += 1;
        
        if (r <= 0)
            s.error(17, std::to_string(r));

        for (int i = 0; i < r; i++) {
            s.newScope(new int(*y), variables, &functions);   
            if (!s.looping) break;
        }

        *y += 1;
    }

    s.looping = false;
    scopedown(y, s.expressions);
}
