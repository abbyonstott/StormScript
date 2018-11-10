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
    char compt;

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
    comp = getval(current_vars, &line);
    line+=2;
    compto = getval(current_vars, &line);

    // compare
    char t = comp.type;

    if (t == compto.type) {
        if (compt == 'i') {
            switch (t) {
                case 'i': condition = ((comp.valint == compto.valint) ? true : false);
                    break;
                case 's': condition = ((comp.valstring) == compto.valstring);
                    break;
                case 'b': condition = ((comp.val) == compto.val);
                    break;
            }
        }
        else{
            switch (t) {
                case 'i': condition = ((comp.valint != compto.valint) ? true : false);
                    break;
                case 's': condition = ((comp.valstring) != compto.valstring);
                    break;
                case 'b': condition = ((comp.val) != compto.val);
                    break;
            }
        }
    }
    else { error(9, compto.name); }


    return condition;
}