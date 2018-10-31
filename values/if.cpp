#include "../core/stsclasses.h"

// checks if string can be converted to int
bool isint(string s) {
    for (int i = 0; i<s.size(); i++) {
        if (std::isdigit(s[i])) {
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

bool sts::compare(int line, std::vector<stsvars> current_vars) {
    bool condition = 0;
    bool nonvar = 0;
    
    char compt;
    char comptype; // the type of literals being compared.
    int valint;
    string valstring;
    bool val;

    stsvars comp;
    stsvars compto;

    prs[line+2].pop_back();

    // check if "is" or "not"
    if (prs[line+1]=="is") {
        compt = 'i';
    }
    else if (prs[line+1]=="not") {
        compt = 'n';
    }
    else {
        error(3, prs[line+1]);
    }

    // check if variable
    if ((isint(prs[line+2])) || (prs[line+2][0]=='"') || (prs[line+2]=="true") || (prs[line+2]=="false")) { 
        if (isint(prs[line+2])) { 
            comptype='i'; 
            valint = std::stoi(prs[line+2]);
        }
        else if (prs[line+2][0]=='"') { 
            comptype='s';
            valstring = striplit(prs[line+2]);
        }
        else { 
            comptype='b';
            if (prs[line+2]=="true") {
                val = true;
            }
            else {
                val = false;
            }
        }
        nonvar = true;
    }

    // set compares
    for (int x = 0; x<current_vars.size(); x++) {
        if (current_vars[x].name == prs[line]) {
            comp = current_vars[x];
        }

        if (!nonvar) {
            if (current_vars[x].name == prs[line+2]) {
                compto = current_vars[x];
                val = compto.val;
                valint = compto.valint;
                valstring = compto.valstring;
                comptype = compto.type;
            }
        }
    }

    // if variable not found
    if ((!nonvar) && (compto.name=="\0")) {
        error(12, prs[line+2]);
    }

    // compare
    char t = comp.type;

    if (t == comptype) {
        if (compt == 'i') {
            switch (t) {
                case 'i': condition = ((comp.valint == valint) ? true : false);
                    break;
                case 's': condition = ((comp.valstring) == valstring);
                    break;
                case 'b': condition = ((comp.val) == val);
                    break;
            }
        }
        else{
            switch (t) {
                case 'i': condition = ((comp.valint != valint) ? true : false);
                    break;
                case 's': condition = ((comp.valstring) != valstring);
                    break;
                case 'b': condition = ((comp.val) != val);
                    break;
            }
        }
    }
    else { error(9, compto.name); }


    return condition;
}