#include "../include/stormscript.h"

/* 
This file deals with non-keyword commands like:
    variable manipulation
    functions
    class type declarations
*/

bool sts::valchange(std::vector<stsvars> * pvars, std::vector<stsclasstype> *classtypes, int * ln){ //changes the value of the stsvars list
    std::vector<stsvars> vars = *pvars;
    int y = *ln;
    std::vector<stsclasstype> ct = *classtypes;

    if (prs[y].back() == ':') {
        pvars->push_back(declare(ln, pvars));
        
        return true;
    }

    // find in libfuncs
    if (names.size()!=0){
        for (int z = 0; z<=names.size()-1 && names[z-1]!=prs[y]; z++){
            if (names[z]==prs[y]) {
                y++;
                runlibfunc(names[z], &y, vars);

                *ln = y;
                *classtypes = ct;
                *pvars = vars;
                
                return true;
            }
        }
    }

    if (functions.size()!=0){
        runfunc(&vars, &ct, &y);
        *ln = y;
        *classtypes = ct;
        *pvars = vars;
        
        return true;
    }

    if (classes.size()!=0) {
        for (int i = 0; i<classes.size() && classes[i-1].name!=prs[y]; i++){
            if (classes[i].name==prs[y]) {
                ct.resize(ct.size()+1);
                ct.back().tpe = classes[i];
                y++;
                ct.back().name = prs[y];

                for (int b = 0; b<ct[ct.size()-1].tpe.variables.size(); b++) {
                    vars.resize(vars.size()+1);
                    vars.back().name = ct[i].name + "|" + ct[i].tpe.variables[b].name;
                    vars.back().type = ct[i].tpe.variables[b].type;
                    ct[i].indexes.push_back(vars.size()-1); // dump index for reading during execution of method
                }

                for (int b = 0; b<ct[ct.size()-1].tpe.methods.size(); b++) {
                    functions.push_back(ct[i].tpe.methods[b]);
                    functions.back().name = ct[i].name + "|" + ct[i].tpe.methods[b].name;
                    functions.back().cof = ct[i].name;
                }
                y++;

                *ln = y;
                *classtypes = ct;
                *pvars = vars;
                
                return true;
            }

        }
    }

    return false;
}