#include "../core/stsclasses.h"

/*
stsdec.cpp: basic type declarations
*/

void stsvars::assignlist(sts *stsscript, std::vector<stsvars> vars, int *line) {
    sts script = *stsscript;
    int y = *line;
    std::vector<string> prs = script.prs;

    y++;
    while (prs[y]!="]") { // add variables to list
        vals.resize(vals.size()+1);
        vals[vals.size()-1]=script.getval(vars, &y);
        y++;
    }
    y++;

    *line = y;
    *stsscript = script;
}


stsvars sts::declare(char type, int line, std::vector<stsvars> *vars) { //variable declarations
    stsvars new_var;
    new_var.type = type;
    
    int y = line+1;

    new_var.name = prs[line];
    // bad idea to pop back the line, just pop back the var

    new_var.name.pop_back();

    switch (type) {
        case 'i': new_var.valint=getval(*vars, &y).valint;
            break;
        case 'b': new_var.val=getval(*vars, &y).val;
            break;
        case 's': new_var.valstring=getval(*vars, &y).valstring;
            new_var.length = new_var.valstring.size();
            vars->push_back(stsvars());
            vars->back().name = new_var.name + "|length";
            vars->back().valint = new_var.length;
            vars->back().type = 'i';
            break;
        case 'l': new_var.assignlist(this, *vars, &y);
            new_var.length = new_var.vals.size();
            vars->push_back(stsvars());
            vars->back().name = new_var.name + "|length";
            vars->back().valint = new_var.length;
            vars->back().type = 'i';
            break;
    }

    return new_var;
}