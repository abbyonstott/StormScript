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
                    ;
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