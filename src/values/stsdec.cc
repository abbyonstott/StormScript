#include "../include/stormscript.h"

/*
stsdec.cc: basic type declarations
*/

void stsvars::assignlist(sts *stsscript, std::vector<stsvars> vars, int *line) {
    sts script = *stsscript;
    int y = *line;
    std::vector<string> prs = script.prs;

    vals.erase(vals.begin(), vals.end());
    y++;
    while (prs[y]!="]") { // add variables to list
        vals.push_back(script.getval(vars, &y));
        y++;
    }
    y++;

    *line = y;
    *stsscript = script;
}


void sts::define(int *line, std::vector<stsvars> *vars) { //variable declarations
    int num = vars->size();
    if (isvar(vars, expressions[*line].contents, &num)) {
        *line += 2;
        vars->at(num) = getval(*vars, line);
    }
    else {
        vars->push_back(stsvars());
        *line += 2;
        vars->back() = getval(*vars, line);
        vars->back().name = expressions[*line-2].contents;
    }

    switch (vars->at(num).type) {
        case 's':
            vars->at(num).length = vars->at(num).val.size();
            break;
        case 'l':
            vars->at(num).length = vars->at(num).vals.size();
            break;
    }

    *line += 1;
}