#include "../core/stsclasses.h"

/* 
This file deals with non-keyword commands like:
    variable manipulation
    functions
    class type declarations
*/

string striplit(string line) {
    line.pop_back();
    line.erase(line.begin());

    return line;
}

bool isint(string s) {
    for (int i = 0; i<s.size(); i++) {
        if (std::isdigit(s[i]))
            return true;
        else
            return false;
    }
    return false;
}

void sts::valchange(std::vector<stsvars> * pvars, std::vector<stsclasstype> *classtypes, int * ln){ //changes the value of the stsvars list
    std::vector<stsvars> vars = *pvars;
    int y = *ln;
    std::vector<stsclasstype> ct = *classtypes;

    if (prs[y][prs[y].size()-1]==':') { // variable manipulation operation
        int varnum;
        string line = prs[y];
        prs[y].pop_back();


        if ((prs[y][prs[y].size()-1]=='-') || (prs[y][prs[y].size()-1]=='+'))
            prs[y].pop_back();

        // loops through var names
        for (int i = 0; i<vars.size() && prs[y]!=vars[i-1].name; i++)
            varnum = ((vars[i].name==prs[y]) ? i : -1);

        // change value if is vars
        if (varnum!=-1){
            y++;
            *ln = y;
            if (line.find("+")!=string::npos) { // add
                switch (vars[varnum].type) {
                    case 'i': vars[varnum].valint += getval(vars, ln).valint;
                        break;
                    case 's': vars[varnum].valstring += getval(vars, ln).valstring;
                        break;
                    case 'b': error(3, "+");
                        break;
                }
            }
            else if (line.find("-")!=string::npos) { // subtract
                switch (vars[varnum].type) {
                    case 'i': vars[varnum].valint -= getval(vars, ln).valint;
                        break;
                    case 's': error(3, "-");
                        break;
                    case 'b': error(3, "-");
                        break;
                }
            }
            else{ // change value
                switch (vars[varnum].type) {
                    case 'i': vars[varnum].valint = getval(vars, ln).valint;
                        break;
                    case 's': vars[varnum].valstring = getval(vars, ln).valstring;
                        break;
                    case 'b': vars[varnum].val = getval(vars, ln).val;
                        break;
                }
            }
            y++;
        }
        else
            error(12, prs[y]);
    }


    // find in libfuncs
    if (names.size()!=0){
        for (int z = 0; z<=names.size()-1 && names[z-1]!=prs[y]; z++){
                y++;
                runlibfunc(names[z], &y);
        }
    }

    if (functions.size()!=0){
        for (int z = 0; z<=functions.size()-1; z++){
            if (functions[z].name==prs[y]){
                if (prs[y+1]=="=>"){
                    y+=3;
                    for (int i = 0; i<functions[z].args.size(); i++) {
                        char *argtype = &functions[z].args[i].type;
                    
                        stsvars argval = getval(vars, &y);


                        switch (*argtype) {
                            case 's': functions[z].args[i].valstring = argval.valstring;
                                break;
                            case 'b': functions[z].args[i].val = argval.val;
                                break;
                            case 'i': functions[z].args[i].valint = argval.valint;
                                break;
                        }
                        y+=2;
                    }
                    exec(functions[z].linestarted, z);
                }
                else {
                    exec(functions[z].linestarted, z);
                    y++;
                }
                break;
            }
        }
    }

    /*if (classes.size()!=0) {
        for (int i = 0; i<classes.size() && classes[i-1].name!=prs[y]; i++){
            ct.resize(ct.size()+1);
            ct[ct.size()-1].tpe = classes[i];
            y++;
            ct[ct.size()-1].name = prs[y];
            
            for (int b = 0; b<ct[ct.size()-1].tpe.variables.size(); b++) {
                vars.resize(vars.size()+1);

                
            }
        }
        y++;
    }
    if (ct.size()!=0) {
        for (int i = 0; i<ct.size(); i++) {
            if (ct[i].name==prs[y]) {
                y++;
                prs[y].pop_back();
                ct[i].type='c';
                for (int d = 0; d<ct[i].tpe.variables.size(); d++) {
                    if (ct[i].tpe.variables[d].name==prs[y]) {
                        y++;
                        
                        bool bval = false;
                        if (prs[y]=="true"){ bval = true; }

                        string name = ct[i].name + "|" + ct[i].tpe.variables[d].name;

                        vars.resize(vars.size()+1);

                        switch (ct[i].tpe.variables[d].type) {
                            case 'i': ct[i].tpe.variables[d].valint = std::stoi(prs[y]);
                                break;
                            case 'b': ct[i].tpe.variables[d].val = bval;
                                break;
                            case 's': ct[i].tpe.variables[d].valstring = striplit(prs[y]);
                                break;
                        }
                        vars[vars.size()-1] = ct[i].tpe.variables[d];
                        vars[vars.size()-1].name=name;
                        y++;
                    } 
                }
            }
        }
    }*/
    *ln = y;
    *classtypes = ct;
    *pvars = vars;
}