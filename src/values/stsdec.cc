#include "../include/stormscript.h"

/*
stsdec.cc: basic type declarations
*/

void sts::declareFunc(int *y, std::vector<stsfunc> *functions) {
    functions->push_back(stsfunc());

    *y += 1;
    functions->back().name = expressions[*y].contents;

    *y += 2;

    int endreq = 1;

    while (endreq != 0)  {
        if (expressions[*y].tktype == OPENCURL) endreq += 1;
        else if (expressions[*y].tktype == CLOSEDCURL) endreq -= 1;

        functions->back().contents.push_back(expressions[*y]);

        *y += 1;
    }

    functions->back().contents.pop_back(); // remove last line as it is just a closed curl
    *y -= 1;
}

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