#include "../include/stormscript.h"

void sts::sys(int *y, std::vector<stsvars> vars){
    int line = *y;
    line++;

    if (prs[line][0]=='"') {
        string cmd = prs[line];
        cmd.pop_back();
        cmd.erase(cmd.begin());
        system(cmd.c_str());
    }
    else{
        for (int x = 0; x<vars.size(); x++) {
            if (vars[x].name==prs[line]) {
                if (vars[x].type=='s') {
                    string val = vars[x].val;
                    system(val.c_str());
                    line++;
                }
                else if (vars[x].type=='i')
                    error(10, "int");

                else if (vars[x].type == 'b')
                    error(10, "bool");
            }
        }
    }
    *y = line;
}