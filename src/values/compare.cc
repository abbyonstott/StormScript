#include "../include/stormscript.h"

int subscript(std::vector<string> prs, int y) {
    int n = 0;

    /*
    prs should look like this if there is 2 subscripts
    y+ | line
    ---|-----
    0: var1
    1: [
    2: n
    3: ]
    4: comparison operator
    5: var2
    6: [
    7: n
    8: ]
    
    And if there is one on the left
    0: var1
    1: [
    2: n
    3: ]
    4: comparison operator
    5: var2

    and if there is one on the right
    0: var1
    1: comparison operator
    2: var2
    3: [
    4: n
    5: ]
    */

    if (prs[y+1] == "[") {
        n++;

        if (prs[y+6] == "[")
            n++;
    }
    else if (prs[y+3] == "[")
        n++;

    return n;
}

bool condition(sts *program, int *ln, std::vector<stsvars> vars) {
    std::vector<string> prs = program->prs;
    sts prg = *program;
    int y = *ln;
    int sbs = subscript(program->prs, y);
    bool v;

    if (sbs == 0)
        prg.prs = { program->prs[y] };
    else {
        prg.prs = { program->prs[y], program->prs[y+1], program->prs[y+2], program->prs[y+3] };
        y+= 3;
    }

    int sy = y + 2;

    stsvars val1 = prg.getval(vars, new int(0));

    if (sbs <= 1)
        prg.prs = { program->prs[sy] };
    else {
        prg.prs = { program->prs[sy], program->prs[sy+1], program->prs[sy+2], program->prs[sy+3] };
        y+=2;
    }

    stsvars val2 = prg.getval(vars, new int(0));
    
    if (val1.type == val2.type) {
        // compare based on conditional operator
        if (prs[y+1] == "is")
            v = (val1.val == val2.val);
        else if (prs[y+1] == "not")
            v = (val1.val != val2.val);
        else if (prs[y+1] == "greater") {
            switch (val1.type) {
                case 'i':
                    v = (std::stoi(val1.val) > std::stoi(val2.val));
                    break;
                case 's':
                case 'b':
                    program->error(3, prs[y] + " " + prs[y+1] + " " + prs[y+2]);
                    
            }
        }
        else if (prs[y+1] == "greatereq") {
            switch (val1.type) {
                case 'i':
                    v = (std::stoi(val1.val) >= std::stoi(val2.val));
                    break;
                case 's':
                case 'b':
                    program->error(3, prs[y] + " " + prs[y+1] + " " + prs[y+2]);
            }
        }
        else if (prs[y+1] == "less") {
            switch (val1.type) {
                case 'i':
                    v = (std::stoi(val1.val) < std::stoi(val2.val));
                    break;
                case 's':
                case 'b':
                    program->error(3, prs[y] + " " + prs[y+1] + " " + prs[y+2]);
                    
            }
        }
        else if (prs[y+1] == "lesseq") {
            switch (val1.type) {
                case 'i':
                    v = (std::stoi(val1.val) <= std::stoi(val2.val));
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