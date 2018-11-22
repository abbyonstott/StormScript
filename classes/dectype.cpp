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
            variables.back().type = 'i'; 
            ln++;
            variables.back().name = prs[ln];  
            ln++;
        }
        else if (prs[ln]=="str") {
            variables.resize(variables.size()+1);
            variables.back().type = 's';
            ln++;
            variables.back().name = prs[ln];
            ln++;
        }
        else if (prs[ln]=="bool") {
            variables.resize(variables.size()+1);
            variables.back().type = 'b';
            ln++;
            variables.back().name = prs[ln];
            ln++;
        }
        else if (prs[ln]=="func") {
            decmethod(inst, &ln);
        }
        else if (prs[ln]=="}") {
            break;
        }

    }

    *y = ln;
}