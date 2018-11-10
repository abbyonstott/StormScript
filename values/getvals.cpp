#include "../core/stsclasses.h"

stsvars sts::getval(std::vector<stsvars> vars, int *line) {
    stsvars v;
    int y = *line;

    if (isint(prs[y])) {
        v.type = 'i';
        v.valint = std::stoi(prs[y]);
    }
    else if (prs[y].front() == '"') {
        v.type = 's';
        if (prs[y].back() == '"') {
            v.valstring = striplit(prs[y]);
        }
        else {
            error(14, prs[y]);
        }
    }
    else if ((prs[y] == "true") || (prs[y]=="false")) {
        v.type = 'b';
        v.val = (prs[y]=="true");
    }
    else {
        for (int x = 0; x<vars.size(); x++) {
            if (vars[x].name==prs[y]) {
                v = vars[x];
            }
        }
        for (int x = 0; x<functions.size(); x++) {
            if (functions[x].name==prs[y]) {
                exec(functions[x].linestarted, x);
                v = functions[x];
            }
        }
    }

    *line = y;
    return v;
}