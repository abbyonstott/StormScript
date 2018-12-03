#include "../core/stsclasses.h"

stsvars sts::getval(std::vector<stsvars> vars, int *line) {
    stsvars v;
    int y = *line;

    if (prs[y+1]=="+") {
        /* 
        This is addition. It can add numbers and use them in print, definitions, and if statements.
        ex:
        if x+1 is 3 {
            printl "It's ", x+1, "!";
        }
        */
        v = math(&y);
        *line = y;
        return v;
    }

    if (isint(prs[y])) {
        v.type = 'i';
        v.valint = std::stoi(prs[y]);
    }
    else if (prs[y].front() == '"') {
        v.type = 's';
        if (prs[y].back() == '"') {
            v.valstring = striplit(prs[y]);
            if (isint(v.valstring))
                v.valint = std::stoi(v.valstring);
        }
        else
            error(14, prs[y]);

        v.length = v.valstring.size();
    }
    else if ((prs[y] == "true") || (prs[y]=="false")) {
        v.type = 'b';
        v.val = (prs[y]=="true");
    }
    else if (prs[y+1]=="[") {
        string name = prs[y];
        y+=2;
        int index = getval(vars, new int(y)).valint;

        for (int i = 0; i<vars.size() && vars[i-1].name != name; i++) {
            if (vars[i].name == name) {
                try{ // set v to index
                    if (vars[i].type == 'l')
                        v = vars[i].vals[index];
                    else if (vars[i].type == 's') {
                        v.type = 's';
                        v.valstring = vars[i].valstring[index];
                        if (index>=vars[i].valstring.size())
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
                    if (v.type == 's')
                        v.valstring = output;
                    else
                        v.valint = std::stoi(output);
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