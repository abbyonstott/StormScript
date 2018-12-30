#include "../include/stormscript.h"

// this is only to declare methods, not to reference or use them.

void stsclass::decmethod(sts *inst, int *ln) {
    int y = *ln;
    y++;

    methods.resize(methods.size()+1);
    
    methods.back().name = inst->prs[y]; //set name to next line
    methods.back().classmethod = true;
    
    y++;
    methods.back().linestarted = y;

    while (inst->prs[y]!="}")
        y++;
        
    *ln = y;
}