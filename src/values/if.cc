#include "../include/stormscript.h"

void sts::ifs(int *line, int *endr, std::vector<stsvars> vars) {
    int y = *line;
    int endreq = *endr;
    y++;
    *line = y;

    if (!toBool(getval(vars, line).val)){
        y = *line;
        y++;
        while (prs[y] != "}") {
            y++;
            if (prs[y+1] == "else") {
                if (prs[y+2] == "if") {
                    y+= 2;
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
    else {
        y = *line;
        
        if (prs[y-1] == "[")
            y+= 2;
        else
            y++;
    }

    *line = y;
    *endr = endreq;
}