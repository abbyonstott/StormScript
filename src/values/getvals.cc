#include "../include/stormscript.h"

stsvars sts::getval(std::vector<stsvars> vars, int *line) {
    /*
    THIS FILE IS VERY IMPORTANT!!!!!
    When Modifying this function be sure that:
        a. The code works in every circumstance where a value would be needed (act as though any value is grabbed with one expression; add to y until it reaches the end of the expression)
        b. The code uses returns a value with a type. Under no circumstance should the variable "v" have an empty type.
        c. This should go without saying, but please document your code. I don't want to remove anything important because I can't figure out what it does
    */

    stsvars v;
    int y = *line;

    bool operation = ((expressions[y+1].t == TOKEN) && (expressions.size() > y+1));

    switch (operation) {
        case 0: // if raw value
            if (expressions[y].t == VALUE) { // returns literals with proper types
                string lit;

                switch (expressions[y].literalType) {
                    case STRING:
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
            else if (expressions[y].t == UNKNOWN)
                    v = findVar(vars, expressions[y].contents); // otherwise get value from variable

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
                index = std::stoi(placeholders[0].getval(vars, new int(0)).val);
            }

            switch (t) { // perform based on token type
                case PLUS: // START MATH
                    v.val = std::to_string(std::stoi(placeholders.at(0).getval(vars, new int(0)).val) + std::stoi(placeholders.at(1).getval(vars, new int(0)).val));
                    break;
                case MINUS:
                    v.val = std::to_string(std::stoi(placeholders.at(0).getval(vars, new int(0)).val) - std::stoi(placeholders.at(1).getval(vars, new int(0)).val));
                    break;
                case DIVISION:
                    v.val = std::to_string(std::stoi(placeholders.at(0).getval(vars, new int(0)).val) / std::stoi(placeholders.at(1).getval(vars, new int(0)).val));
                    break;
                case MULTIPLICATION:
                    v.val = std::to_string(std::stoi(placeholders.at(0).getval(vars, new int(0)).val) * std::stoi(placeholders.at(1).getval(vars, new int(0)).val));
                    break; // END MATH
                case OPENBRACKET:
                    plus1 = expressions[placeholders[0].expressions.size() + y + 1].tktype;
                    if ((expressions[placeholders[0].expressions.size() + y + 1].t != TOKEN) && ((plus1 != IS) || (plus1 != NOT) || (plus1 != GREATER) || (plus1 != GREATEREQ) || (plus1 != LESS) || (plus1 != LESSEQ))) {
                        sbsvar = findVar(vars, expressions[y-2].contents);

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
                                if ((index >= sbsvar.vals.size()) || (index < 0)) {
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
                    v.type = 'b';
                    v.val = ((condition(this, &y, vars)) ? "true" : "false");
                    break;
            }

            break;
    }

    *line = y;
    return v;
}
    /*
    else if (((prs[y+1] == "is") || (prs[y+1] == "not") || (prs[y+1] == "greater") || (prs[y+1] == "greatereq") || (prs[y+1] == "less") || (prs[y+1] == "lesseq")) || ((prs[y+1]=="[") && ((prs[y+4] == "is") || (prs[y+4] == "not") || (prs[y+4] == "greater") || (prs[y+4] == "greatereq") || (prs[y+4] == "less") || (prs[y+4] == "lesseq")))) {
        bool cond  = condition(this, &y, vars);
        // check if ternary;
        y+=2;
        if (prs[y+1] == "?") {
            y+=2;
            if (cond) {
                v = getval(vars, &y);
                y+=2;
            }
            else {
                y+=2;
                v = getval(vars, &y);
            }
            *line = y;
            return v;
        }
        else {
            *line = y;
            v.type = 'b';
            v.val = ((cond) ? "true" : "false");
            return v;
        }
    }

    else if (prs[y] == "read") {
        y++;
        readfile(y, &v, vars);
        *line = y;
        return v;
    }

    else if (prs[y] == "randomrange") {
        v.type = 'i';
        v.val = std::to_string(genrandomintfromrange(this, vars, &y));
        *line = y;
        return v;
    }

    else if (prs[y] == "random") {
        v.type = 'b';
        v.val = ((randombool()) ? "true" : "false");
        return v;
    }

    else {
        for (int x = 0; x<vars.size(); x++) {
            if (vars[x].name==prs[y])
                v = vars[x];
        }
        for (int x = 0; x<functions.size(); x++) {
            if (functions[x].name==prs[y]) {
                runfunc(&vars, new std::vector<stsclasstype>, &y);
                v = functions[x].value;
            }
        }
    }

    if (v.type=='\000')
        error(12, prs[*line]); 
}*/