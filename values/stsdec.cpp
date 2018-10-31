#include "../core/stsclasses.h"

/*
stsdec.cpp: basic type and function declarations
declare(): variables
*/


stsvars sts::declare(char type, int line, std::vector<stsvars> vars) { //variable declarations
    stsvars new_var;
    new_var.type = type;
    int y = line+1;
    string a; //command to compile
    bool nonvar;
    int valint;
    string valstring;
    bool val;


    prs[line].pop_back();
    new_var.name = prs[line];
    if ((isint(prs[y])) || (prs[y][0]=='"') || (prs[y]=="true") || (prs[y]=="false")) { 
        if (isint(prs[y])) { 
            valint = std::stoi(prs[y]);
        }
        else if (prs[y][0]=='"') { 
            valstring = striplit(prs[y]);
        }
        else { 
            if (prs[y]=="true") {
                val = true;
            }
            else {
                val = false;
            }
        }
        nonvar = true;
    }

    if (!nonvar) {
        for (int i = 0; i<vars.size(); i++) {
            if (vars[i].name==prs[y]) {
                nonvar = false;
                switch (vars[i].type) {
                    case 'i': valint = vars[i].valint;
                        break;
                    case 's': valstring = vars[i].valstring;
                        break;
                    case 'b': val = vars[i].val;
                        break;
                }
            }
        }
    }

    switch (type) {
        case 'i': new_var.valint=valint;
            break;
        case 'b': new_var.val=val;
            break;
        case 's': new_var.valstring=valstring;
    }

    return new_var;
}