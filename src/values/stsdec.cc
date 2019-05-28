#include "../include/stormscript.h"

void sts::declareFunc(int *y, std::vector<stsfunc> *functions) {
    functions->push_back(stsfunc());

    *y += 1;

    functions->back().name = expressions[*y].contents;

    *y += 1;

    if (expressions[*y].tktype == ARROW) {
        *y += 1;

        while (true) {
            functions->back().args.push_back(stsvars());
            functions->back().args.back().name = expressions[*y].contents;
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

        functions->back().contents.push_back(expressions[*y]);

        *y += 1;
    }

    functions->back().contents.pop_back(); // remove last line as it is just a closed curl
    *y -= 1;
}

std::vector<stsvars> 
listgen(sts *script, int *y, std::vector<stsvars> *vars, std::vector<stsfunc> functions) {
    std::vector<stsvars> values;
    *y += 1;

    while (script->expressions[*y-1].tktype != CLOSEDBRACKET) {
        values.push_back(script->getval(vars, functions, y));
        *y+= 2;
    }
    
    *y -= 1;

    return values;
}


void sts::define(int *line, std::vector<stsvars> *vars, std::vector<stsfunc> functions) { //variable declarations
    int num = vars->size();
    string name = expressions[*line].contents;

    if (isvar(vars, name, &num)) {
        /*
        * If already defined this changes the value of 
        * the variable
        */
        *line += 2;
        if (vars->at(num).type != 'l')
            vars->at(num) = getval(vars, functions, line);
        else 
            vars->at(num).vals = listgen(this, line, vars, functions);
        vars->at(num).name = name;
    }
    else {
        vars->push_back(stsvars());
        *line += 2;
        if (expressions[*line].tktype != OPENBRACKET)
            vars->back() = getval(vars, functions,  line);
        else {
            vars->back().type = 'l';
            vars->back().vals = listgen(this, line, vars, functions);
        }

        vars->back().name = name;
    }

    switch (vars->at(num).type) {
        case 's':
            vars->at(num).length = vars->at(num).val.size();
            break;
        case 'l':
            vars->at(num).length = vars->at(num).vals.size();
            break;
    }
    while (expressions[*line].t != ENDEXPR) *line += 1;
}