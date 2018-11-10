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

void sts::ifs(int *line, int *endr, std::vector<stsvars> vars) {
    int y = *line;
    int endreq = *endr;
    y++;

    if (!compare(&y,vars)){
        y++;
        while (prs[y] != "end") {
            y++;
            if (prs[y] == "else") {
                if (prs[y+1] == "if") {
                    y++;
                    ifs(&y, &endreq, vars);
                    break;
                }
                else {
                    y++;
                    break;
                }
            }
        }
    }
    else{
        y++;
    }

    *line = y;
    *endr = endreq;
}

bool sts::compare(int *y, std::vector<stsvars> current_vars) {
    bool condition = 0;
    char compt;
    int line = *y;

    stsvars comp;
    stsvars compto;

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

    *y = line;

    return condition;
}