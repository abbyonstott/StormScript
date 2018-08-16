#include "stsclasses.h"

/*
stsdec.cpp: basic type and function declarations
declare(): variables
fdeclare(): declare functions
checkiffunction(): returns a boolean of if the name is a function or not
*/


stsvars sts::declare(char type, int line){ //variable declarations
    stsvars new_var;
    new_var.type = type;
    string a; //command to compile
    
    prs[line+1].pop_back();
    new_var.name = prs[line+1];
    if (type=='i'){
        prs[line+2].pop_back();
        new_var.valint = std::stoi(prs[line+2]);
    }
    else{
        prs[line+2].pop_back();
        if (prs[line+2][0]='\"'){
            prs[line+2].pop_back();
            prs[line+2].erase(prs[line+2].begin());
        }
        new_var.valstring = prs[line+2];
    }
    return new_var;
}