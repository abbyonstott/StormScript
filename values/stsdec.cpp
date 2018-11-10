#include "../core/stsclasses.h"

/*
stsdec.cpp: basic type and function declarations
declare(): variables
*/


stsvars sts::declare(char type, int line, std::vector<stsvars> vars) { //variable declarations
    stsvars new_var;
    new_var.type = type;
    
    int y = line+1;

    prs[line].pop_back();
    new_var.name = prs[line];
    
    stsvars set_to = getval(vars, &y);

    switch (type) {
        case 'i': new_var.valint=set_to.valint;
            break;
        case 'b': new_var.val=set_to.val;
            break;
        case 's': new_var.valstring=set_to.valstring;
    }

    return new_var;
}