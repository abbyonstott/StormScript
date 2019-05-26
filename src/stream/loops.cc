#include "../include/stormscript.h"

/*std::vector<stsvars> whileloop(sts *script, std::vector<stsvars> variables, int y) {
    std::vector<string> prs = script->prs;
    y++;
    while (condition(script, new int(y), variables))
        ;
        //script->exec(new int(y+3), -1, {}, {}, &variables);

    return variables;
}

std::vector<stsvars> forloop(sts *script, std::vector<stsvars> variables, int y) {
    y++;
    std::vector<string> prs = script->prs;
    int r = std::stoi(script->getval(variables, new int(y)).val);

    if (r <= 0)
        script->error(17, std::to_string(r));

    for (int i = 0; i < r; i++)
        ;
        //script->exec(new int(y+1), -1, {}, {}, &variables);

    return variables;
}

std::vector<stsvars> foreach(sts *script, std::vector<stsvars> variables, int y) {
    string placeholder = script->prs[y+1];
    stsvars val = script->getval(variables, new int(y+3));

    if ((val.type != 's') && (val.type != 'l')) // throw error if not list or string
        script->error(4, val.name);

    for (int i = 0; i < ((val.type == 'l') ? val.vals.size() : val.val.size()); i++) {
        std::vector<stsvars> variables_copy = variables;
        stsvars v;

        if (val.type == 's')
            v.val = string(1, val.val[i]);
        else
            v = val.vals[i];
    
        v.name = placeholder;

        variables_copy.push_back(v);
        
        //script->exec(new int(y+4), -1, {}, {}, &variables_copy);

        for (int x = 0; x < variables.size(); x++)
            variables[x] = variables_copy[x];
    }

    return variables;
}*/