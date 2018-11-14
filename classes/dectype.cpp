#include "../core/stsclasses.h"

void stsclass::declare(int *y, sts *inst) { //declare type
    int ln = *y;
    std::vector<string> prs = inst->prs;

    // get name of type
    ln++;
    name=prs[ln];

    ln++;
    // get type objects
    for (ln; ln<prs.size(); ln++) {
        if (prs[ln]=="int") {
            variables.resize(variables.size()+1);
            variables[variables.size()-1].type = 'i'; 
            ln++;
            variables[variables.size()-1].name = prs[ln];  
            ln++;
        }
        else if (prs[ln]=="str") {
            variables.resize(variables.size()+1);
            variables[variables.size()-1].type = 's';
            ln++;
            variables[variables.size()-1].name = prs[ln];
            ln++;
        }
        else if (prs[ln]=="bool") {
            variables.resize(variables.size()+1);
            variables[variables.size()-1].type = 'b';
            ln++;
            variables[variables.size()-1].name = prs[ln];
            ln++;
        }
        else if (prs[ln]=="end") {
            ln++;
            break;
        }

    }

    *y = ln;
}