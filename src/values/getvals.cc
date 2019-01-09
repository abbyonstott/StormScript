#include "../include/stormscript.h"

stsvars sts::getval(std::vector<stsvars> vars, int *line) {
    stsvars v;
    int y = *line;

    if ((prs[y+1]=="+") || (prs[y+1]=="-") || (prs[y+1]=="*") || (prs[y+1]=="/")) {
        /* 
        This is math. It can add, subtract, multiply, and divide numbers and use them in print, definitions, and if statements.
        ex:
        if x+1 is 3 {
            printl "It's ", x+1, "!";
        }
        */
        stsvars v1, v2;
        v.type='i';

        if (isint(prs[y]))
            v1.val = prs[y];
        else {
            for (int x = 0; x<vars.size(); x++) {
                if (vars[x].name==prs[y])
                    v1 = vars[x];
            }
        }

        if (isint(prs[y+2]))
            v2.val = prs[y+2];
        else {
            for (int x = 0; x<vars.size(); x++) {
                if (vars[x].name==prs[y+2])
                    v2 = vars[x];
            }
        }
        v.val = std::to_string((
            (prs[y+1]=="+") ? std::stoi(v1.val) + std::stoi(v2.val) : (
                (prs[y+1]=="-") ? std::stoi(v1.val) - std::stoi(v2.val) : (
                    (prs[y+1]=="/") ? std::stoi(v1.val) / std::stoi(v2.val) : std::stoi(v1.val) * std::stoi(v2.val)))));
        y+=2;
        *line = y;
        return v;
    }
    else if ((prs[y+1] == "is") || (prs[y+1] == "not") || (prs[y+1] == "greater") || (prs[y+1] == "greatereq") || (prs[y+1] == "less") || (prs[y+1] == "lesseq")) {
        bool cond  = condition(this, &y, vars);
        // check if ternary;
        y+=2;
        if (prs[y+1] == "?") {
            y+=2;
            if (cond) {
                v = getval(vars, &y);
                y+=2;
            }
            else {
                y+=2;
                v = getval(vars, &y);
            }
            *line = y;
            return v;
        }
        else {
            *line = y;
            v.type = 'b';
            v.val = ((cond) ? "true" : "false");
            return v;
        }
    }

    else if (isint(prs[y])) {
        v.type = 'i';
        v.val = prs[y];
    }
    else if (prs[y].front() == '"') {
        v.type = 's';

        if (prs[y].back() == '"')
            v.val = striplit(prs[y]);
        else
            error(14, prs[y]);
    
        v.length = v.val.size();
    }
    else if ((prs[y] == "true") || (prs[y]=="false")) {
        v.type = 'b';
        v.val = prs[y];
    }
    else if (prs[y+1]=="[") {
        string name = prs[y];
        y+=2;
        int index = std::stoi(getval(vars, new int(y)).val);

        for (int i = 0; i<vars.size() && vars[i-1].name != name; i++) {
            if (vars[i].name == name) {
                try{ // set v to index
                    if (vars[i].type == 'l')
                        v = vars[i].vals[index];
                    else if (vars[i].type == 's') {
                        v.type = 's';
                        v.val = vars[i].val[index];
                        if (index>=vars[i].val.size())
                            throw std::bad_alloc(); // throw bad alloc if string is out of range.
                    }
                    else
                        throw 3;
                }
                catch (std::bad_alloc x) { // if out of range throw error
                    string message = prs[y-2] + prs[y-1] + prs[y] + prs[y+1];
                    error(6, message);
                }
                catch (int n) {
                    string message = prs[y-2] + prs[y-1] + prs[y] + prs[y+1];
                    error(n, message);
                }
            }
        }

        y++;
    }

    else {
        for (int x = 0; x<vars.size(); x++) {
            if (vars[x].name==prs[y])
                v = vars[x];
        }
        for (int x = 0; x<functions.size(); x++) {
            if (functions[x].name==prs[y]) {
                runfunc(&vars, new std::vector<stsclasstype>, &y);
                v = functions[x].value;
            }
        }
        if (names.size()!=0){
            for (int z = 0; z<names.size(); z++){
                if (names[z]==prs[y]){
                    y++;
                    string output = runlibfunc(names[z], &y, vars);
                    v.type = ((isint(output)) ? 'i' : 's');
                    v.val = output;
                    y--;
                }
            }
        }
    }

    if (v.type=='\000')
        error(12, prs[*line]);

    *line = y;
    return v;
}