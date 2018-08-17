#include "stsclasses.h"

/*
stsstream.cpp: all of the basic input and output streams.
*/

void sts::out(int line, std::vector<stsvars> current_vars){
    string val = "";

    if (prs[line][0]=='\"'){
        prs[line].erase(prs[line].begin());
        prs[line].pop_back();
        val = prs[line];
    }
    else{
        for (int x = 0; x<=current_vars.size(); x++){
            if (prs[line]==current_vars[x].name){
                if (current_vars[x].type=='i') { val = std::to_string(current_vars[x].valint); }
                else { val = current_vars[x].valstring; }

                break;
            }
        }
    }
    
    for (int x = 0; x<=val.size(); x++){
        if ((val[x]=='\\') && (val[x+1]=='n')){
            val.pop_back();
            val[x]='\n';
        }
    }

    cout << val;
}

stsvars sts::in(int line){
    stsvars input;

    input.name = prs[line+1];

    if (prs[line]=="int"){
        input.type = 'i';
        std::cin >> input.valint;
    }
    else if (prs[line]=="str"){
        input.type = 's';
        std::cin >> input.valstring;
    }

    return input;
}

bool sts::compare(int line, std::vector<stsvars> current_vars){
    bool condition = 0;
    prs[line+2].pop_back();
    for (int x = 0; x<=current_vars.size(); x++){
        if (current_vars[x].name==prs[line]){
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
    }

    return condition;
}