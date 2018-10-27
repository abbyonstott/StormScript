#include "../core/stsclasses.h"

/*
stsdec.cpp: basic type and function declarations
declare(): variables
*/


stsvars sts::declare(char type, int line){ //variable declarations
    stsvars new_var;
    new_var.type = type;
    int y = line+1;
    string a; //command to compile

    prs[line].pop_back();
    new_var.name = prs[line];

    if (type=='i'){
        new_var.valint = std::stoi(prs[y]);
    }
    else if (type=='s'){
        if (prs[y][0]=='\"'){
            prs[y].pop_back();
            prs[y].erase(prs[y].begin());
        }
        new_var.valstring = prs[y];
    }
    else if (type=='b'){
        bool bval = false;
        if (prs[y]=="true"){
            bval=true;
        }
        new_var.val=bval;
    }
    else if (type=='j'){
        while (prs[y]!=";"){
            new_var.valsint.resize(new_var.valsint.size()+1);
            new_var.valsint[new_var.valsint.size()-1]=std::stoi(prs[y]);
            y++;
        }
    }
    else if (type=='t'){
        while (prs[y]!=";"){
            prs[y].pop_back();
            prs[y].erase(prs[y].begin());
            new_var.valsstring.resize(new_var.valsstring.size()+1);
            new_var.valsstring[new_var.valsstring.size()-1]=prs[y];
            y++;
        }
    }
    return new_var;
}