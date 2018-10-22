#include "../core/stsclasses.h"

void sts::valchange(std::vector<stsvars> * pvars, int * ln){ //changes the value of the stsvars list
    std::vector<stsvars> vars = *pvars;
    int y = *ln;
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
                exec(functions[z].linestarted, names, z);
                y++;
                break;
            }
        }
    }
    *ln = y;
    *pvars = vars;
}