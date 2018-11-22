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

bool sts::valchange(std::vector<stsvars> * pvars, std::vector<stsclasstype> *classtypes, int * ln){ //changes the value of the stsvars list
    std::vector<stsvars> vars = *pvars;
    int y = *ln;
    std::vector<stsclasstype> ct = *classtypes;

    if ((prs[y].back()==':') || (prs[y+4] == ":")) { // variable manipulation operation
        int varnum;
        const string name = prs[y];
        const string line = ((prs[y+1] == "[") ? prs[y] + prs[y+1] + prs[y+2] + prs[y+3] + prs[y+4] : prs[y]); // set unmodifiable "copy" to variable[i]:
        string lineorig = line; // set original "copy" to variable[i]:
        lineorig.pop_back();


        if ((lineorig.back()=='-') || (lineorig.back()=='+'))
            lineorig.pop_back();
        
        if (prs[y+1] == "[") {
            lineorig.erase(lineorig.find('['), lineorig.back()); //erase to show name

            vars.push_back(getval(vars, &y));
            vars.back().glob = 0;
            varnum = vars.size()-1;
            *ln += 5;
        }
        // loops through var names
        else {
            for (int i = 0; i<vars.size() && lineorig!=vars[i-1].name; i++)
                varnum = ((vars[i].name==lineorig) ? i : -1);

            y++;
            *ln = y;
        }

        // change value if is vars
        if (varnum!=-1){
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
            
            if (vars[varnum].glob)
                globvars[varnum]=vars[varnum];

            if (prs[y-2] == "[") {
                int ind = 0;

                for (ind; vars[ind].name!=name; ind++) {}
                
                vars[ind].vals[std::stoi(prs[y-1])] = vars.back();
                if (vars[ind].glob)
                    globvars[ind]=vars[ind];

                vars.pop_back();
            }
            for (y; y<=prs.size() && prs[y]!=";"; y++) {} // Increase y until it sees semicolon

            *ln = y;
            *classtypes = ct;
            *pvars = vars;
            
            return true;
            
        }
        else
            error(12, prs[y]);
    }


    // find in libfuncs
    if (names.size()!=0){
        for (int z = 0; z<=names.size()-1 && names[z-1]!=prs[y]; z++){
            if (names[z]==prs[y]) {
                y++;
                runlibfunc(names[z], &y);

                *ln = y;
                *classtypes = ct;
                *pvars = vars;
                
                return true;
            }
        }
    }

    if (functions.size()!=0){
        runfunc(&vars, &ct, &y);
        *ln = y;
        *classtypes = ct;
        *pvars = vars;
        
        return true;
    }

    if (classes.size()!=0) {
        for (int i = 0; i<classes.size() && classes[i-1].name!=prs[y]; i++){
            if (classes[i].name==prs[y]) {
                ct.resize(ct.size()+1);
                ct.back().tpe = classes[i];
                y++;
                ct.back().name = prs[y];

                for (int b = 0; b<ct[ct.size()-1].tpe.variables.size(); b++) {
                    vars.resize(vars.size()+1);
                    vars.back().name = ct[i].name + "|" + ct[i].tpe.variables[b].name;
                    vars.back().type = ct[i].tpe.variables[b].type;
                    ct[i].indexes.push_back(vars.size()-1); // dump index for reading during execution of method
                }

                for (int b = 0; b<ct[ct.size()-1].tpe.methods.size(); b++) {
                    functions.push_back(ct[i].tpe.methods[b]);
                    functions.back().name = ct[i].name + "|" + ct[i].tpe.methods[b].name;
                    functions.back().cof = ct[i].name;
                }
                y++;

                *ln = y;
                *classtypes = ct;
                *pvars = vars;
                
                return true;
            }

        }
    }

    return false;
}