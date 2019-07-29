#include "../include/stormscript.h"

void sts::runBuiltin(int *y) {
    bool l;

    switch (expressions[*y].btn) {
        case PRINT: 
        case PRINTL:
            l = (expressions[*y].btn == PRINTL); // if printl
            while (expressions[*y].t != ENDEXPR) {
                cout << print(y);

                if (expressions[*y+1].tktype == COMMA) *y += 1; // we don't need to add 2 because print() automatically adds 1 to the line counter
            }

            if (l) cout << '\n';
            break;
        case STSIN: 
            thisScope->variables.push_back(in(y));
            break;
        case IF:
            ifs(y);
            break;
        case FUNCTION:
            declareFunc(y);
            break;
        case RETURN:
            if (function > -1) {
                thisScope->functions.at(function).val = getval(new int(*y+1)).val;
                thisScope->functions.at(function).type = getval(new int(*y+1)).type;
                *y = expressions.size(); // return always exits scope
            } 
            else error(7, "");
            
            break;
        case WAIT:
            wait(*y);
            break;
        case WRITE:
            writefile(y);
            break;
        case WHILE:
            whileloop(this, thisScope, y);
            break;
        case FOR:
            forloop(this, thisScope, y);
            break;
        case SYSTEM:
            sys(y);
            break;
        case TYPE:
            declareType(y);
            break;
        case BREAK:
            if (looping) {
                scopedown(y, expressions);
                looping = false;
            }
            else error(6, "");
            break;
        case MODULE:
            /*
            * modules are automatically imported during the error check before runtime
            * all we need to do here is to move on to the next expression
            */
            while (expressions[*y].t != ENDEXPR) *y += 1;
            break;
        case EXIT:
            exit(0);
    }
}

void sts::runUnknown(int *y) {
    int fnum;
    bool shouldbreak;

    switch (expressions[*y+1].t) {
        case TOKEN:
            shouldbreak = 0;

            switch (expressions[*y+1].tktype) {
                case COLON: // definition
                    define(y);
                    shouldbreak = 1;
                    break;
                case ARROW: break;
                case PLUS:
                    if (expressions[*y+2].tktype == COLON) {
                        *y += 3;
                        int n = 0;
                        
                        if (find(&thisScope->variables, expressions[*y-3].contents, &n)) {
                            switch (thisScope->variables.at(n).type) {
                                case 'i':
                                    thisScope->variables.at(n).val = std::to_string(std::stoi(thisScope->variables.at(n).val) + std::stoi(getval(new int(*y)).val));
                                    break;
                                case 'l':
                                    thisScope->variables.at(n).vals.push_back(getval(new int(*y)));
                                    thisScope->variables.at(n).length = thisScope->variables.at(n).vals.size();
                                    break;
                                case 's':
                                    thisScope->variables.at(n).val += getval(new int(*y)).val;
                                    break;
                                case 'b': error(4, thisScope->variables.at(n).name);
                            }
                        }
                        else error(8, expressions[*y-3].contents);

                        shouldbreak = 1;
                    }
                    break;
                case DOT:
                    int ObjNum, MemberNum;
                    
                    // find object
                    find(thisScope->objects, expressions[*y].contents, &ObjNum);

                    if (expressions[*y+3].tktype == ARROW && thisScope->objects[ObjNum].Parentname == "socket") { // socket functions are handled by c++, not stormscript
                        if (expressions[*y+2].contents == "await") {
                            *y += 4;
                            if (expressions[*y].t != VALUE && expressions[*y].t != UNKNOWN) 
                                error(5, "await"); // generic "function requires args error"
                            
                            string msg = getval(y).val; // message to be sent to client

                            *y += 2;
                            bool output = toBool(getval(y).val); // determines whether to output connection or not

                            awaitSocket(thisScope->objects[ObjNum], msg, output);
                        }
                        shouldbreak = true;
                        break;
                    }
                    
                    *y += 2;

                    // find member or method

                    if (expressions[*y+1].tktype == COLON) {

                        find(&thisScope->objects[ObjNum].members, expressions[*y].contents, &MemberNum);

                        stsvars newval = getval(y);

                        if (thisScope->objects[ObjNum].members[MemberNum].type == newval.type) 
                            thisScope->objects[ObjNum].members[MemberNum].val = newval.val;
                        else error(2, expressions[*y].contents);
                    }
                    else {
                        find(thisScope->objects[ObjNum].methods, expressions[*y].contents, &MemberNum);

                        sts typests;

                        typests.expressions.push_back(expression());
                        typests.expressions[0] = expressions[*y];

                        *y += 1;

                        if (expressions[*y].tktype == ARROW) {
                            while (expressions[*y].t != ENDEXPR) {
                                typests.expressions.push_back(expression());
                                typests.expressions.back() = expressions[*y];

                                *y += 1;
                            }
                        }

                        typests.expressions.push_back(expression());
                        typests.expressions.back() = expressions[*y];
                        
                        typests.thisScope->functions.push_back(thisScope->objects[ObjNum].methods[MemberNum]);
                        typests.thisScope->variables.insert(typests.thisScope->variables.begin(), thisScope->objects[ObjNum].members.begin(), thisScope->objects[ObjNum].members.end());

                        typests.runfunc(new int(0), 0);

                        thisScope->objects[ObjNum].members = typests.thisScope->variables;
                    }

                    shouldbreak = true;

                    break;
            }

            if (shouldbreak) break;
        case ENDEXPR:
            find(thisScope->functions, expressions[*y].contents, &fnum); // run isFunc to get function number
            runfunc(y, fnum);
            break;
        case UNKNOWN:
            declareObject(y);
            break;
    }
}

void sts::interp(int psize, char *argv[], int argc){
    parse(prg);
    parseErrors();

    thisScope->variables.resize(thisScope->variables.size()+1);
    for (int x = 1; x<=argc-1; x++) {
        thisScope->variables.back().type='l';
        thisScope->variables.back().vals.resize(thisScope->variables.back().vals.size()+1);
        thisScope->variables.back().vals.back().type = 's';
        thisScope->variables.back().vals.back().val=argv[x];
        thisScope->variables.back().name="arg";
        thisScope->variables.back().length = argc-1;
    }
    thisScope->types.push_back(socketClass());
    
    
    newScope(new int(0));
}