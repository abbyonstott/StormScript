#include "../core/stsclasses.h"

void sts::sys(int line){
    prs[line].pop_back();
    prs[line].erase(prs[line].begin());
    system(prs[line].c_str());
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
