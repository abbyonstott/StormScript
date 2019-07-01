#include "../include/stormscript.h"

void sts::declareType(int *y) {
    *y += 1;

    type t;

    t.name = expressions[*y].contents;
    
    *y += 2;

    while (expressions[*y].tktype != CLOSEDCURL) {
        stsvars obj;
        stsfunc c;

        switch (expressions[*y].btn) {
            case TYPE_INTEGER:
            case TYPE_STRING:
            case TYPE_LIST:
            case TYPE_STS_BOOL:
                if (expressions[*y].btn == TYPE_STS_BOOL) obj.type = 'b';
                else if (expressions[*y].btn == TYPE_INTEGER) obj.type = 'i';
                else if (expressions[*y].btn == TYPE_STRING) obj.type = 's';
                else obj.type = 'l';
                
                obj.name = expressions[++(*y)].contents;
                *y += 1;

                t.members.push_back(obj);
                break;

            case CONSTRUCTOR_SCOPE:
                *y += 1;
                c.name = "init";
                
                if (expressions[*y].tktype == ARROW) {
                    *y += 1;

                    while (true) {

                        if (expressions[*y].tktype == OPENCURL) break;
                        else if (expressions[*y].tktype != COMMA) {
                            c.args.push_back(stsvars());
                            c.args.back().name = expressions[*y].contents;
                        }
                        *y += 1;
                    }
                }

                *y += 1;

                int endreq = 1;

                while (endreq != 0) {
                    if (expressions[*y].tktype == CLOSEDCURL) endreq--;
                    else if (expressions[*y].tktype == OPENCURL) endreq++;

                    c.contents.push_back(expressions[*y]);

                    *y += 1;
                }
                
                *y -= 1;

                t.methods.push_back(c);
                break;
        }

        *y += 1;
    }

    thisScope->types.push_back(t);
}

void sts::declareObject(int *y) {
    int num;
    find(thisScope->types, expressions[*y].contents, &num);

    stsObject t = thisScope->types[num];

    t.name = expressions[++(*y)].contents;

    if (t.methods.size() > 0 && t.methods[0].name == "init") {
        sts typests;

        typests.thisScope->functions.push_back(t.methods[0]);
        typests.thisScope->variables.insert(typests.thisScope->variables.begin(), t.members.begin(), t.members.end());

        typests.expressions.push_back(expression());
        typests.expressions[0].contents = "init";
        typests.expressions[0].line = 1;
        // if there are arguments
        if (expressions[*y + 1].tktype == ARROW && thisScope->types[num].methods[0].args.size() > 0) {
            *y += 1;
            
            while (expressions[*y].t != ENDEXPR) {
                typests.expressions.push_back(expression());
                typests.expressions.back().contents = expressions[*y].contents;
                typests.expressions.back().line = 1;

                *y += 1;
            }
        }
        else if (expressions[*y + 1].tktype == ARROW) // if user gives arguments when there are none
            error(10, t.Parentname);

        typests.expressions.push_back(expression());
        typests.expressions.back().line = 1;
        typests.expressions.back().contents = ";";

        typests.evaluateProgram();
        typests.runfunc(new int(0), 0);

        t.members = typests.thisScope->variables;
    }

    thisScope->objects.push_back(t);
}