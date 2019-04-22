#include "../include/stormscript.h"

std::vector<stsvars> whileloop(sts *script, std::vector<stsvars> variables, int y) {
    std::vector<string> prs = script->prs;
    y++;
    while (condition(script, new int(y), variables))
        script->exec(new int(y+3), -1, {}, {}, &variables);

    return variables;
}

std::vector<stsvars> forloop(sts *script, std::vector<stsvars> variables, int y) {
    y++;
    std::vector<string> prs = script->prs;
    int r = std::stoi(script->getval(variables, new int(y)).val);

    if (r <= 0)
        script->error(17, std::to_string(r));

    for (int i = 0; i < r; i++)
        script->exec(new int(y+1), -1, {}, {}, &variables);

    return variables;
}