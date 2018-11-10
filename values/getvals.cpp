#include "../core/stsclasses.h"

stsvars sts::getval(std::vector<string> prs, int *line) {
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

    *line = y;
    return v;
}