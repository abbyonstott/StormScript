#include "../core/stsclasses.h"

string striplit(string line) {
    line.pop_back();
    line.erase(line.begin());

    return line;
}

void sts::valchange(std::vector<stsvars> * pvars, std::vector<stsclasstype> *classtypes, int * ln){ //changes the value of the stsvars list
    std::vector<stsvars> vars = *pvars;
    int y = *ln;
    std::vector<stsclasstype> ct = *classtypes;

    if (vars.size()!=0){
        if (prs[y].size()!=1){
            string s = prs[y];
            s.pop_back();
            for (int z = 0; z<=vars.size()-1; z++){
                if (s == vars[z].name){
                    if (vars[z].type=='i'){
                        vars[z].valint = std::stoi(prs[y+1]);
                        if (vars[z].glob==1) { globvars[z].valint = std::stoi(prs[y+1]); }
                    }
                    else{
                        prs[y+1].pop_back();
                        prs[y+1].erase(prs[y+1].begin());
                        vars[z].valstring = prs[y+1];
                        if (vars[z].glob==1) { globvars[z].valstring = prs[y+1]; }
                    }
                    y++;
                    break;
                }
                else if (s == vars[z].name+'+'){ // plus operator
                    

                    if (vars[z].type=='i'){
                        vars[z].valint += std::stoi(prs[y+1]);
                        if (vars[z].glob==1) { globvars[z].valint += std::stoi(prs[y+1]); }
                    }
                    else if (vars[z].type=='j'){
                        vars[z].valsint.resize(vars[z].valsint.size()+1);
                        vars[z].valsint[vars[z].valsint.size()-1]=std::stoi(prs[y+1]);
                    }
                    else{
                        prs[y+1].pop_back();
                        prs[y+1].erase(prs[y+1].begin());
                        vars[z].valstring += prs[y+1];
                        if (vars[z].glob==1) { globvars[z].valstring += prs[y+1]; }
                    }
                    y+=2;
                    break;
                }
                else if (s == vars[z].name+'-'){ // minus operator
                    
                    if (vars[z].type=='i'){
                        vars[z].valint -= std::stoi(prs[y+1]);
                        if (vars[z].glob==1) { globvars[z].valint += std::stoi(prs[y+1]); }
                    }
                    else {
                        char type = vars[z].type;
                        string types;
                        if (type=='s') types="str"; 
                        error(4, types);
                    }
                    y++;
                    break;
                }
            }
        }       
    }
    if (names.size()!=0){
        for (int z = 0; z<=names.size()-1; z++){
            if (names[z]==prs[y]){
                y++;
                string cmd1;
                string cmd0 = names[z];
                if (PLATFORM=="Windows"){
                    cmd1 = "stslib.exe ";
                }
                else{
                    cmd1 = ".stslib ";
                }
                cmd0+=cmd1.c_str();
                cmd0+=prs[y].c_str();
                if (prs[y][prs[y].size()-1]==':'){
                    cmd0[cmd0.size()-1]=' ';
                    y++;
                    prs[y].erase(prs[y].begin());
                    prs[y].pop_back();
                    cmd0+=prs[y].c_str();
                }
                system(cmd0.c_str());
                y++;
            }
        }
    }
    if (functions.size()!=0){
        for (int z = 0; z<=functions.size()-1; z++){
            if (functions[z].name==prs[y]){
                if (prs[y+1]=="=>"){
                    y+=3;
                    for (int i = 0; i<functions[z].args.size(); i++) {
                        char *argtype = &functions[z].args[i].type;
                    
                        bool bval = false;
                        if (prs[y]=="true"){ bval = true; }


                        switch (*argtype) {
                            case 's': functions[z].args[i].valstring = striplit(prs[y]);
                                break;
                            case 'b': functions[z].args[i].val = bval;
                                break;
                            case 'i': functions[z].args[i].valint = std::stoi(prs[y]);
                                break;
                        }
                        y+=2;
                    }
                    exec(functions[z].linestarted, names, z);
                }
                else {
                    exec(functions[z].linestarted, names, z);
                    y++;
                }
                break;
            }
        }
    }
    if (classes.size()!=0) {
        for (int i = 0; i<classes.size(); i++) {
            if (classes[i].name==prs[y]) {
                ct.resize(ct.size()+1);
                ct[ct.size()-1].tpe = classes[i];
                y++;
                ct[ct.size()-1].name = prs[y];
                y++;
            }
        }
    }
    if (ct.size()!=0) {
        for (int i = 0; i<ct.size(); i++) {
            if (ct[i].name==prs[y]) {
                y++;
                prs[y].pop_back();
                for (int d = 0; d<ct[i].tpe.variables.size(); d++) {
                    if (ct[i].tpe.variables[d].name==prs[y]) {
                        y++;
                        
                        bool bval = false;
                        if (prs[y]=="true"){ bval = true; }

                        switch (ct[i].tpe.variables[d].type) {
                            case 'i': ct[i].tpe.variables[d].valint = std::stoi(prs[y]);
                                break;
                            case 'b': ct[i].tpe.variables[d].val = bval;
                                break;
                            case 's': ct[i].tpe.variables[d].valstring = striplit(prs[y]);
                                break;
                        }
                        y++;
                    } 
                }
            }
        }
    }
    *ln = y;
    *classtypes = ct;
    *pvars = vars;
}