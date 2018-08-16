#include "stsclasses.h"

/*
stsstream.cpp: all of the basic input and output streams.
*/

void sts::out(int line, std::vector<stsvars> current_vars){
    string val = "";

    prs[line+1].pop_back();
    if (prs[line+1][0]=='\"'){
        prs[line+1].erase(prs[line+1].begin());
        prs[line+1].pop_back();
        val = prs[line+1];
    }
    else{
        for (int x = 0; x<=current_vars.size(); x++){
            if (prs[line+1]==current_vars[x].name){
                if (current_vars[x].type=='i') { val = std::to_string(current_vars[x].valint); }
                else { val = current_vars[x].valstring; }

                break;
            }
        }
    }

    cout << val << endl;
}

stsvars sts::in(int line){
    stsvars input;

    prs[line+2].pop_back();
    input.name = prs[line+2];

    if (prs[line+1]=="int"){
        input.type = 'i';
        std::cin >> input.valint;
    }
    else if (prs[line+1]=="str"){
        input.type = 's';
        std::cin >> input.valstring;
    }

    return input;
}

bool sts::compare(int line, std::vector<stsvars> current_vars){
    bool condition = 0;
    prs[line+3].pop_back();
    for (int x = 0; x<=current_vars.size(); x++){
        if (current_vars[x].name==prs[line+1]){
            if ((current_vars[x].type=='i') && (current_vars[x].valint==std::stoi(prs[line+3]))){
                condition=1;
            }

            else if (current_vars[x].type=='s'){
                if (prs[line+3][0]=='\"'){
                    prs[line+3].erase(prs[line+3].begin());
                    prs[line+3].pop_back();
                    if (prs[line+3]==current_vars[x].valstring){
                        condition=1;
                    }
                }
            }

        }
    }

    return condition;
}