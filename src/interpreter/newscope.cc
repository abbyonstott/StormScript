#include "../include/stormscript.h"

void sts::newScope(int *y, std::vector<stsvars> vars) {
    for (*y; *y < expressions.size() && expressions[*y].tktype != CLOSEDCURL; *y += 1) {
        
        switch(expressions[*y].t) { // don't need to worry about TOKEN and ENDEXPR because they will be handled inside of functions
            case BUILTIN: 
                runBuiltin(y, &vars);
                break;
            case UNKNOWN: 
                runUnknown(y, &vars);
                break;
        }
    
    }
}