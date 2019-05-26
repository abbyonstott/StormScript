#include "../include/stormscript.h"

void sts::runfunc(int *y, std::vector<stsfunc> *functions, std::vector<stsvars> *variables, int num) {
    sts functionsts;
    std::vector<stsvars> fvars = *variables;

    functionsts.function = num;
    functionsts.expressions = functions->at(num).contents;

    fvars.insert(fvars.end(), functions->at(num).args.begin(), functions->at(num).args.end());

    int argbegin = variables->size(); 

    if (functions->at(num).args.size() > 0) {
        if (expressions[*y+1].tktype != ARROW)
            error(18, functions->at(num).name);
        else {
            *y += 2;

            int argon = 0;
            
            while (true) {
                fvars[argbegin + argon] = getval(variables, *functions, y);
                fvars[argbegin + argon].name = functions->at(num).args[argon].name;

                *y += 1;
                if (expressions[*y].t == ENDEXPR) break;
                else if (expressions[*y].tktype == COMMA) {
                    *y += 1;
                    argon += 1;
                }
            }
        }
    }

    functionsts.newScope(new int(0), &fvars, functions);
}