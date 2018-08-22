#include "stsclasses.h"

/*
stsdec.cpp: basic type and function declarations
declare(): variables
*/


stsvars sts::declare(char type, int line){ //variable declarations
    stsvars new_var;
    new_var.type = type;
    string a; //command to compile

    prs[line].pop_back();
    new_var.name = prs[line];
    if (type=='i'){
        new_var.valint = std::stoi(prs[line+1]);
    }
    else{
        if (prs[line+1][0]=='\"'){
            prs[line+1].pop_back();
            prs[line+1].erase(prs[line+1].begin());
        }
        new_var.valstring = prs[line+1];
    }
    return new_var;
}