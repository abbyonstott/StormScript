#include "../include/stormscript.h"

stsvars sts::getval(std::vector<stsvars> *vars, std::vector<stsfunc> functions, int *line) {
    /*
    THIS FILE IS VERY IMPORTANT!!!!!
    When Modifying this function be sure that:
        a. The code works in every circumstance where a value would be needed (act as though any value is grabbed with one expression; add to y until it reaches the end of the expression)
        b. The code uses returns a value with a type. Under no circumstance should the variable "v" have an empty type.
        c. This should go without saying, but please document your code. I don't want to remove anything important because I can't figure out what it does
    */

    stsvars v;
    int y = *line;

    bool operation = ((expressions[y+1].t == TOKEN) && (expressions[y+1].tktype != COMMA) && (expressions[y+1].tktype != COLON) && (expressions[y+1].tktype != OPENCURL)  && (expressions[y+1].tktype != CLOSEDBRACKET) && (expressions.size() > y+1));

    switch (operation) {
        case 0: // if raw value
            if (expressions[y].t == VALUE) { // returns literals with proper types
                string lit;

                switch (expressions[y].literalType) {
                    case STRING: // TODO: allow concatenation
                        lit = striplit(expressions[y].contents);
                        v.type = 's';
                        v.length = lit.size();
                        break;
                    case INTEGER:
                    case BOOLEAN:
                        v.type = ((expressions[y].literalType == INTEGER) ? 'i' : 'b');
                        lit = expressions[y].contents;
                        break;
                }

                v.val = lit;
            }
            else if (expressions[y].t == BUILTIN) { 
                // read just reads the file, but it is always used as a value because it returns a value
                switch (expressions[y].btn) { 
                    case READ:
                        v = readfile(&y, vars, functions);
                        break;
                    case RANDOM:
                        v.val = ((randombool()) ? "true" : "false");
                        v.type = 'b';
                        break;
                    case RANDOMRANGE:
                        v.val = std::to_string(genrandomintfromrange(this, vars, functions, &y));
                        v.type = 'i';
                }
            }
            else if (expressions[y].t == UNKNOWN) {
                int index;

                if (isvar(vars, expressions[y].contents, &index)) v = vars->at(index); // use index to find variable if the expression refers to a variable
                else if (isFunc(functions, expressions[y].contents, &index)) {
                    runfunc(&y, &functions, vars, index);
                    v = functions[index]; // if expression refers to function
                }
            }

            break;
        case 1: // if operation
            TokenType t = expressions[y+1].tktype;
            std::vector<sts> placeholders;
            int index;
            stsvars sbsvar;
            TokenType plus1;

            if ((t == PLUS) || (t == MINUS) || (t == DIVISION) || (t == MULTIPLICATION)) { 
                // all math operations will return an integer, so we can set that first
                v.type = 'i';

                placeholders.resize(2);

                placeholders.at(0).expressions = {expressions[y]};
                placeholders.at(1).expressions = {expressions[y+2]};

                y+= 2;
            }
            else if (t == OPENBRACKET) {
                y += 2;
                int er = 1;
                int i = y;

                placeholders.resize(1);

                while (er != 0) {
                    if ((expressions[i].t == TOKEN) && (expressions[i].tktype == CLOSEDBRACKET))
                        er--;
                    else if ((expressions[i].t == TOKEN) && (expressions[i].tktype == OPENBRACKET))
                        er++;

                    if (er != 0)
                        placeholders.back().expressions.push_back(expressions[i]);
                    
                    i++;
                }
                index = std::stoi(placeholders[0].getval(vars, functions, new int(0)).val);
            }

            switch (t) { // perform based on token type
                case PLUS: // I'm sure there is an easier way to do this...
                    v.val = std::to_string(std::stoi(placeholders.at(0).getval(vars, functions, new int(0)).val) + std::stoi(placeholders.at(1).getval(vars, functions, new int(0)).val));
                    break;
                case MINUS:
                    v.val = std::to_string(std::stoi(placeholders.at(0).getval(vars, functions, new int(0)).val) - std::stoi(placeholders.at(1).getval(vars, functions, new int(0)).val));
                    break;
                case DIVISION:
                    v.val = std::to_string(std::stoi(placeholders.at(0).getval(vars, functions, new int(0)).val) / std::stoi(placeholders.at(1).getval(vars, functions, new int(0)).val));
                    break;
                case MULTIPLICATION:
                    v.val = std::to_string(std::stoi(placeholders.at(0).getval(vars, functions, new int(0)).val) * std::stoi(placeholders.at(1).getval(vars, functions, new int(0)).val));
                    break; 
                case OPENBRACKET:
                    plus1 = expressions[placeholders[0].expressions.size() + y + 1].tktype;
                    if ((expressions[placeholders[0].expressions.size() + y + 1].t != TOKEN) && ((plus1 != IS) || (plus1 != NOT) || (plus1 != GREATER) || (plus1 != GREATEREQ) || (plus1 != LESS) || (plus1 != LESSEQ))) {
                        sbsvar = findVar(*vars, expressions[y-2].contents);

                        switch(sbsvar.type) {
                            case 's':
                                if ((index >= sbsvar.val.size()) || (index < 0)) {
                                    string fullexpr = sbsvar.name + "[";

                                    for (int n = 0; n < placeholders[0].expressions.size(); n++) // add full subscript to error details
                                        fullexpr += placeholders[0].expressions[n].contents;

                                    fullexpr += "]"; // add brackets for complete statement

                                    error(6, fullexpr);
                                }

                                v.type = 's';
                                v.val = sbsvar.val[index];

                                break;

                            case 'l':
                                if ((index >= sbsvar.vals.size()) || (index < 0)) { // out of range error
                                    string fullexpr = sbsvar.name + "[";

                                    for (int n = 0; n < placeholders[0].expressions.size(); n++) // add full subscript to error details
                                        fullexpr += placeholders[0].expressions[n].contents;

                                    fullexpr += "]"; // add brackets for complete statement

                                    error(6, fullexpr);
                                }

                                v = sbsvar.vals[index];

                                break;

                            case 'i': // subscripts don't work on int or bool, so give error
                            case 'b':
                                error(9, sbsvar.name);
                                break;
                        }

                        break;
                    }
                    else
                        y -= 2;
                case IS:
                case NOT:
                case GREATER:
                case GREATEREQ:
                case LESS:
                case LESSEQ:
                    v.val = ((condition(this, &y, vars,  functions)) ? "true" : "false");
                    if (expressions[y].tktype == TERNARY1) {
                        /* 
                        For ternary, we can assume that it is structured like this:
                           TOKEN   | VALUE/UNKNOWN |   TOKEN   | VALUE/UNKNOWN
                        -----------|---------------------------|--------------
                            ?      |     var       |     :     |     var

                        as usual, these values can be anything, but getval() automatically fills in the gap so we don't have to do much here with different cases
                        */
                        bool _val = toBool(v.val);
                        stsvars primary, secondary;

                        primary = getval(vars, functions, new int(y+1));

                        while (expressions[y].tktype != COLON) y++; 
                        y++;
                        secondary = getval(vars, functions, new int(y));

                        v.val = ((_val) ? primary.val : secondary.val);
                        v.type = ((_val) ? primary.type : secondary.type);
                    }
                    break;
            }

            break;
    }

    *line = y;
    return v;
}