#include "../include/stormscript.h"

void sts::runfunc(int *y, int num) {
    sts functionsts;

    std::vector<stsvars> _variables = thisScope->variables;

    thisScope->variables.insert(thisScope->variables.end(), 
        thisScope->functions.at(num).args.begin(), thisScope->functions.at(num).args.end());

    functionsts.function = num;
    functionsts.expressions = thisScope->functions.at(num).contents;

    int argbegin = _variables.size(); 

    if (thisScope->functions.at(num).args.size() > 0) {
        if (expressions[*y+1].tktype != ARROW)
            error(5, thisScope->functions.at(num).name);
        else {
            *y += 2;

            int argon = 0;
            
            while (true) {
                thisScope->variables[argbegin + argon] = getval(y);
                thisScope->variables[argbegin + argon].name = thisScope->functions.at(num).args[argon].name;

                *y += 1;
                if (expressions[*y].t == ENDEXPR) break;
                else if (expressions[*y].tktype == COMMA) {
                    *y += 1;
                    argon += 1;
                }
            }
        }
    }

    functionsts.thisScope = thisScope;
    functionsts.newScope(new int(0));

    _variables.insert(_variables.begin(), 
        thisScope->variables.begin(), thisScope->variables.begin() + _variables.size());

    thisScope->variables = _variables;
}