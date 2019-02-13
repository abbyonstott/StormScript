#include "../include/stormscript.h"

std::vector<stsvars> whileloop(sts *script, std::vector<stsvars> variables, int y) {
    std::vector<string> prs = script->prs;
    y++;
    while (condition(script, new int(y), variables)) {
        script->exec(new int(y+3), -1, {}, {}, &variables);
    }


    return variables;
}