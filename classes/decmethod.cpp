#include "../core/stsclasses.h"

void stsclass::decmethod(sts *inst, int *ln) {
    *ln++;
    inst->functions.resize(inst->functions.size()+1);

    inst->functions.back().classmethod = true; // tell stormscript that the function is a class method

    inst->functions.back().name = inst->prs[*ln]; //set name to next line

    *ln++;
    inst->functions.back().linestarted = *ln;

    while (inst->prs[*ln-1]!="end")
        *ln++;
}