#include "../include/stormscript.h"

void sts::runfunc(std::vector<stsvars> * pvars, std::vector<stsclasstype> *classtypes, int * ln) {
    std::vector<stsvars> vars = *pvars;
    int y = *ln;
    std::vector<stsclasstype> ct = *classtypes;

    for (int z = 0; z<=functions.size()-1; z++){
        if (functions[z].name==prs[y]){
            if (prs[y+1]=="=>"){
                y++;
                for (int i = 0; i<functions[z].args.size(); i++) {
                    y+=2;
                    char *argtype = &functions[z].args[i].type;
                
                    stsvars argval = getval(vars, new int(y));


                    switch (*argtype) {
                        case 's': functions[z].args[i].val = argval.val;
                            functions[z].args[i].length = argval.length;
                            break;
                        case 'b': functions[z].args[i].val = argval.val;
                            break;
                        case 'i': functions[z].args[i].val = argval.val;
                            break;
                    }
                }
                exec(new int(functions[z].linestarted), z, {}, {});
            }
            else {
                std::vector<stsvars*> o;

                if (functions[z].classmethod) {
                    for (int i = 0; i<ct.size(); i++) {
                        if (ct[i].name==functions[z].cof) {
                            for (int x = 0; x<ct[i].indexes.size(); x++)
                                o.push_back(&vars[ct[i].indexes[x]]);
                        }
                    }
                }

                exec(new int(functions[z].linestarted), z, classtypes, o);

            }
            *ln = y;
            *classtypes = ct;
            *pvars = vars;

            for (int i = 0; i<globvars.size(); i++) {
                pvars->at(i) = globvars[i];
            }
        }
    }
}