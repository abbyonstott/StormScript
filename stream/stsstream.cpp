#include "../core/stsclasses.h"

void sts::sys(int line, std::vector<stsvars> vars){
    if (prs[line][0]=='"'){
        prs[line].pop_back();
        prs[line].erase(prs[line].begin());
        system(prs[line].c_str());
    }
    else{
        for (int x = 0; x<=vars.size()-1; x++) {
            if (vars[x].type=='s') {
                string val = vars[x].valstring;
                system(val.c_str());
            }
            else if (vars[x].type=='i'){
                error(10, "int");
            }
            else if (vars[x].type == 'b'){
                error(10, "bool");
            }
        }
    }
}

bool sts::compare(int line, std::vector<stsvars> current_vars){
    bool condition = 0;
    prs[line+2].pop_back();
    for (int x = 0; x<=current_vars.size(); x++){
        if (current_vars[x].name==prs[line]){
            if (prs[line+1]=="is"){ //compared with 'is' expression
                if ((current_vars[x].type=='i') && (current_vars[x].valint==std::stoi(prs[line+2]))){
                    condition=1;
                }  

                else if (current_vars[x].type=='s'){
                    if (prs[line+2][0]=='\"'){
                        prs[line+2].erase(prs[line+2].begin());
                        prs[line+2].pop_back();
                        if (prs[line+2]==current_vars[x].valstring){
                            condition=1;
                        }
                    }
                    else { error(9, prs[line+2]); }
                }
                else if (current_vars[x].type=='b'){
                    if (prs[line+2]=="true"){ if (current_vars[x].val==true){ condition = 1; } }
                    else if (prs[line+2]=="false"){ if (current_vars[x].val==true){ condition = 1; } }
                    else { error(9, prs[line+2]); }
                }
            }
            else if (prs[line+1]=="not"){ // compared with 'not' expression
                if ((current_vars[x].type=='i') && (current_vars[x].valint!=std::stoi(prs[line+2]))){
                    condition=1;
                }  

                else if (current_vars[x].type=='s'){
                    if (prs[line+2][0]=='\"'){
                        prs[line+2].erase(prs[line+2].begin());
                        prs[line+2].pop_back();
                        if (prs[line+2]!=current_vars[x].valstring){
                            condition=1;
                        }
                    }
                }
            }
            else{
                error(3,prs[line+1]);
            }
        }
    }

    return condition;
}
