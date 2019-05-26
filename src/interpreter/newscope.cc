#include "../include/stormscript.h"

void sts::newScope(int *y, std::vector<stsvars> vars, std::vector<stsfunc> *functions) {
    int oldfsize = functions->size();

    for (*y; *y < expressions.size() && expressions[*y].tktype != CLOSEDCURL; *y += 1) {
        
        switch(expressions[*y].t) { // don't need to worry about TOKEN and ENDEXPR because they will be handled inside of functions
            case BUILTIN: 
                runBuiltin(y, &vars, functions);
                break;
            case UNKNOWN: 
                runUnknown(y, &vars, functions);
                break;
        }
    
    }

    functions->erase(functions->begin() + oldfsize, functions->end());
}