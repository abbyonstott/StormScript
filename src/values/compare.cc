#include "../include/stormscript.h"

bool condition(sts *program, int *ln, std::vector<stsvars> vars) {
    std::vector<string> prs = program->prs;
    sts prg = *program;
    int y = *ln;
    bool v;

    prg.prs = { program->prs[y] };


    stsvars val1 = prg.getval(vars, new int(0));

    if (program->prs[y+3] != "[")
        prg.prs = { program->prs[y+2] };
    else {
        prg.prs = { program->prs[y+2], program->prs[y+3], program->prs[y+4] };
        y+=2;
    }

    stsvars val2 = prg.getval(vars, new int(0));
    
    if (val1.type == val2.type) {
        // compare based on conditional operator
        if (prs[y+1] == "is") {
            v = (val1.val == val2.val);
        }
        else if (prs[y+1] == "not") {
            v = (val1.val != val2.val);
        }
        else if (prs[y+1] == "greater") {
            switch (val1.type) {
                case 'i':
                    v = (val1.val > val2.val);
                    break;
                case 's':
                case 'b':
                    program->error(3, prs[y] + " " + prs[y+1] + " " + prs[y+2]);
                    
            }
        }
        else if (prs[y+1] == "greatereq") {
            switch (val1.type) {
                case 'i':
                    v = (val1.val >= val2.val);
                    break;
                case 's':
                case 'b':
                    program->error(3, prs[y] + " " + prs[y+1] + " " + prs[y+2]);
            }
        }
        else if (prs[y+1] == "less") {
            switch (val1.type) {
                case 'i':
                    v = (val1.val < val2.val);
                    break;
                case 's':
                case 'b':
                    program->error(3, prs[y] + " " + prs[y+1] + " " + prs[y+2]);
                    
            }
        }
        else if (prs[y+1] == "lesseq") {
            switch (val1.type) {
                case 'i':
                    v = (val1.val <= val2.val);
                    break;
                case 's':
                case 'b':
                    program->error(3, prs[y] + prs[y+1] + prs[y+2]);
                    
            }
        }
    }
    else {
        // give error with value based on type
        program->error(9, val2.val);
    }
    *ln = y;

    return v;
}