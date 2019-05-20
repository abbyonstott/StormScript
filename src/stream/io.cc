#include "../include/stormscript.h"

string sts::print(int *y, std::vector<stsvars> current_vars){ //handles both print and printl.
    int ln = *y;
    ln++;
    stsvars v = getval(current_vars, &ln);
    string value = v.val;
    
    /*for (int x = 0; x<=value.size(); x++) {
        if (value[x] == '\\') {
            if (value[x+1]=='n') {
                value.erase(value.begin() + x);
                value[x]='\n';
            }
            else if (value[x+1] == '\\') {
                value.erase(value.begin() + x);
                value[x]='\\';
            }
            else if (value[x+1] == 't') {
                value.erase(value.begin() + x);
                value[x]='\t';
            }
        }
    }

    if (ln-2 >= 0 && prs[ln-2] == "]")
       ln-=2;*/
    *y = ln;
    return value;
}

stsvars sts::in(int line){
    stsvars input;

    input.name = expressions[line+1].contents;
    input.type = 's';

    char valstring[256]; // allocate a 256 bit char array for value storage

    std::cin.getline(valstring, 256); // use std::cin.getline to get value
    input.val = valstring;
    
    input.length = input.val.size();

    return input;
}
