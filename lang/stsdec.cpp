#include "stsclasses.h"

/*
stsdec.cpp: basic type and function declarations
declare(): variables
fdeclare(): declare functions
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
        if (prs[line+1][0]='\"'){
            prs[line+1].pop_back();
            prs[line+1].erase(prs[line+1].begin());
        }
        new_var.valstring = prs[line+1];
    }
    return new_var;
}

stsfunc sts::fdeclare(int line){
    stsfunc new_func;
    line++;

    if (prs[line]=="int"){
        new_func.type='i';
    }
    else if (prs[line]=="str"){
        new_func.type='s';
    }
    else if (prs[line]=="void"){
        new_func.type='v';
    }
    else{
        error(2,prs[line]);
    }
    prs[line+1].pop_back();
    new_func.name = prs[line+1];
    new_func.line = line+1;
    return new_func;
}