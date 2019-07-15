#include "../include/stormscript.h"

void sts::newScope(int *y) {
    std::vector<stsfunc> _functions = thisScope->functions;
    std::vector<stsvars> _variables = thisScope->variables;
    std::vector<type> _types = thisScope->types;
    std::vector<stsObject> _objects = thisScope->objects;

    while ((expressions[*y].tktype != CLOSEDCURL) && (*y < expressions.size())) {
        
        switch(expressions[*y].t) { // don't need to worry about TOKEN and ENDEXPR because they will be handled inside of functions
            case BUILTIN:
                if (expressions[*y].btn != STSSOCKET) {
                    runBuiltin(y);
                    break;
                }
            case UNKNOWN:
                runUnknown(y);
                break;
        }

        *y += 1;
    }

    thisScope->variables.erase(thisScope->variables.begin() + _variables.size(), thisScope->variables.end());
    thisScope->objects.erase(thisScope->objects.begin() + _objects.size(), thisScope->objects.end());

    _variables = thisScope->variables;
    _objects = thisScope->objects;

    thisScope = new scope(_functions, _variables, _types); // reset size back to original
}