#include "../include/stormscript.h"

string sts::print(int *y, std::vector<stsvars> *current_vars, std::vector<stsfunc> functions){ //handles both print and printl.
    int ln = *y;
    ln++;
    stsvars v = getval(current_vars, functions,  &ln);
    string value = v.val;

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
