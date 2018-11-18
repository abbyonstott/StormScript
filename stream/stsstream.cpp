#include "../core/stsclasses.h"

void sts::sys(int *y, std::vector<stsvars> vars){
    int line = *y;
    line++;
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