#include "../core/stsclasses.h"

void sts::ifs(int *line, int *endr, std::vector<stsvars> vars) {
    int y = *line;
    int endreq = *endr;
    y++;

    if (!compare(&y,vars)){
        y++;
        while (prs[y] != "}") {
            y++;
            if (prs[y+1] == "else") {
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
    if ((prs[line+1]=="is") || ((prs[line+1]=="[") && (prs[line+4]=="is"))) // equal to
        compt = 'i';
    
    else if ((prs[line+1]=="not") || ((prs[line+1]=="[") && (prs[line+4]=="not"))) // not equal to
        compt = 'n';
    
    else if ((prs[line+1]=="less") || ((prs[line+1]=="[") && (prs[line+4]=="less"))) // less than
        compt = 'l';

    else if ((prs[line+1]=="greater") || ((prs[line+1]=="[") && (prs[line+4]=="greater"))) // greater than
        compt = 'g';

    else if ((prs[line+1]=="lesseq") || ((prs[line+1]=="[") && (prs[line+4]=="lesseq"))) // less than or equal to
        compt = 'm';
    
    else if ((prs[line+1]=="greatereq") || ((prs[line+1]=="[") && (prs[line+4]=="greatereq"))) // greater than or equal to
        compt = 'h';
    
    else
        error(3, prs[line+1]);

    // check if variable
    comp = getval(current_vars, &line);
    line+=2;
    compto = getval(current_vars, &line);

    // compare
    char t = comp.type;

    if (t == compto.type) {
        if (compt == 'i') {
            switch (t) {
                case 'i': condition = (comp.valint == compto.valint);
                    break;
                case 's': condition = (comp.valstring == compto.valstring);
                    break;
                case 'b': condition = (comp.val == compto.val);
                    break;
            }
        }
        else if (compt == 'l') {
            switch (t) {
                case 'i': condition = (comp.valint < compto.valint);
                    break;
                case 's':
                case 'b': error(3, "less");
                    break;
            }
        }
        else if (compt == 'g') {
            switch (t) {
                case 'i': condition = (comp.valint > compto.valint);
                    break;
                case 's': 
                case 'b': error(3, "greater");
                    break;
            }
        }
        else if (compt == 'm') {
            switch (t) {
                case 'i': condition = (comp.valint >= compto.valint);
                    break;
                case 's': 
                case 'b': error(3, "lesseq");
                    break;
            }
        }
        else if (compt == 'h') {
            switch (t) {
                case 'i': condition = (comp.valint >= compto.valint);
                    break;
                case 's': 
                case 'b': error(3, "greatereq");
                    break;
            }
        }
        else{
            switch (t) {
                case 'i': condition = (comp.valint != compto.valint);
                    break;
                case 's': condition = (comp.valstring != compto.valstring);
                    break;
                case 'b': condition = (comp.val != compto.val);
                    break;
            }
        }
    }
    else { error(9, compto.name); }

    *y = line;

    return condition;
}