#include "../include/stormscript.h"

void sts::declareFunc(int *y) {
    thisScope->functions.push_back(stsfunc());

    *y += 1;

    thisScope->functions.back().name = expressions[*y].contents;

    *y += 1;

    if (expressions[*y].tktype == ARROW) {
        *y += 1;

        while (true) {
            thisScope->functions.back().args.push_back(stsvars());
            thisScope->functions.back().args.back().name = expressions[*y].contents;
            *y += 1;

            if (expressions[*y].tktype == OPENCURL) break;
            else if (expressions[*y].tktype == COMMA) *y += 1;
        }
        
    }
    *y += 1;

    int endreq = 1;

    while (endreq != 0)  {
        if (expressions[*y].tktype == OPENCURL) endreq += 1;
        else if (expressions[*y].tktype == CLOSEDCURL) endreq -= 1;

        thisScope->functions.back().contents.push_back(expressions[*y]);

        *y += 1;
    }

    thisScope->functions.back().contents.pop_back(); // remove last line as it is just a closed curl
    *y -= 1;
}

std::vector<stsvars> 
listgen(sts *script, int *y) {
    std::vector<stsvars> values;
    *y += 1;

    while (script->expressions[*y-1].tktype != CLOSEDBRACKET) {
        values.push_back(script->getval(y));
        *y+= 2;
    }
    
    *y -= 1;

    return values;
}


void sts::define(int *line) { //variable declarations
    int num = thisScope->variables.size();
    string name = expressions[*line].contents;

    if (isvar(&thisScope->variables, name, &num)) {
        /*
        * If already defined this changes the value of 
        * the variable
        */
        *line += 2;
        if (thisScope->variables.at(num).type != 'l')
            thisScope->variables.at(num) = getval(line);
        else 
            thisScope->variables.at(num).vals = listgen(this, line);
        thisScope->variables.at(num).name = name;
    }
    else {
        thisScope->variables.push_back(stsvars());
        *line += 2;
        if (expressions[*line].tktype != OPENBRACKET)
            thisScope->variables.back() = getval(line);
        else {
            thisScope->variables.back().type = 'l';
            thisScope->variables.back().vals = listgen(this, line);
        }

        thisScope->variables.back().name = name;
    }

    switch (thisScope->variables.at(num).type) {
        case 's':
            thisScope->variables.at(num).length = thisScope->variables.at(num).val.size();
            break;
        case 'l':
            thisScope->variables.at(num).length = thisScope->variables.at(num).vals.size();
            break;
    }
    while (expressions[*line].t != ENDEXPR) *line += 1;
}