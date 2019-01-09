#include "../include/stormscript.h"

void sts::print(int line, int *y, std::vector<stsvars> current_vars){ //handles both print and printl.
    int ln = *y;
    stsvars v = getval(current_vars, &ln);
    string value = v.val;
    
    for (int x = 0; x<=value.size(); x++) {
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

    input.name = prs[line];
    input.type = 's';

    char valstring[256]; // allocate a 256 bit char array for value storage

    std::cin.getline(valstring, 256); // use std::cin.getline to get value
    input.val = valstring;
    
    input.length = input.val.size();

    return input;
}