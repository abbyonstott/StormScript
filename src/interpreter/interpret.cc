#include "../include/stormscript.h"

void sts::runBuiltin(int *y, std::vector<stsvars> *scpvars, std::vector<stsfunc> *functions) {
    bool l;

    switch (expressions[*y].btn) {
        case PRINT: 
        case PRINTL:
            l = (expressions[*y].btn == PRINTL); // if printl
            while (expressions[*y].t != ENDEXPR) {
                cout << print(y, scpvars, *functions);

                if (expressions[*y+1].tktype == COMMA) *y += 1; // we don't need to add 2 because print() automatically adds 1 to the line counter
            }

            if (l) cout << '\n';
            break;
        case IN: 
            scpvars->push_back(in(*y));
            break;
        case IF:
            ifs(scpvars, *functions, y);
            break;
        case FUNCTION:
            declareFunc(y, functions);
            break;
        case RETURN:
            if (function > -1) {
                functions->at(function).val = getval(scpvars, *functions, new int(*y+1)).val;
                functions->at(function).type = getval(scpvars, *functions, new int(*y+1)).type;
                *y = expressions.size(); // return always exits scope
            } 
            else error(7, "");
            
            break;
        case WAIT:
            wait(scpvars, *functions, *y);
            break;
        case WRITE:
            writefile(y, scpvars, *functions);
            break;
        case WHILE:
            whileloop(this, scpvars, *functions, y);
            break;
        case FOR:
            forloop(this, scpvars, *functions, y);
            break;
        case SYSTEM:
            sys(y, scpvars, *functions);
            break;
        case EXIT:
            exit(0);
    }
}

void sts::runUnknown(int *y, std::vector<stsvars> *scpvars, std::vector<stsfunc> *functions) {
    int fnum;
    bool shouldbreak;

    switch (expressions[*y+1].t) {
        case TOKEN:
            shouldbreak = 0;

            switch (expressions[*y+1].tktype) {
                case COLON: // definition
                    define(y, scpvars, *functions);
                    shouldbreak = 1;
                    break;
                case ARROW: break;
            }

            if (shouldbreak) break;
        case ENDEXPR:
            switch (isFunc(*functions, expressions[*y].contents, &fnum)) { // if there is a semicolon directly after, it is either a function or not a command
                case 0: 
                    error(1, expressions[*y].contents);
                    break;
                case 1: 
                    runfunc(y, functions, scpvars, fnum);
                    break;
            }
            break;
    }
}

void sts::interp(string fname, int psize, char *argv[], int argc){
    parse(prg);

    std::vector<stsfunc> functions;
    std::vector<stsvars> variables;

    variables.resize(variables.size()+1);
    for (int x = 1; x<=argc-1; x++) {
        variables.back().type='l';
        variables.back().vals.resize(variables.back().vals.size()+1);
        variables.back().vals.back().type = 's';
        variables.back().vals.back().val=argv[x];
        variables.back().name="arg";
        variables.back().length = argc-1;
    }
    
    newScope(new int(0), &variables, &functions);
}