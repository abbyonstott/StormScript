#include "../include/stormscript.h"

void sts::print(int line, int *y, std::vector<stsvars> current_vars){ //handles both print and printl.
    int ln = *y;
    stsvars val = getval(current_vars, &ln);
    string value = val.val;
    
    for (int x = 0; x<=value.size(); x++){
        if ((value[x]=='\\') && (value[x+1]=='n')){
            value.pop_back();
            value[x]='\n';
        }
    }

    *y = ln;

    cout << value;
}

stsvars sts::in(int line){
    stsvars input;

    input.name = prs[line+1];

    if (prs[line]=="int"){
        input.type = 'i';
        std::cin >> input.val;
    }
    else if (prs[line]=="str"){
        input.type = 's';
        char valstring[256];
        std::cin.getline(valstring, 256);
        input.val=valstring;
    }
    else if (prs[line]=="bool") {
        input.type = 'b';
        std::cin >> input.val;
    }

    return input;
}