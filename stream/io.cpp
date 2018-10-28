#include "../core/stsclasses.h"

void sts::print(int line, int *y, std::vector<stsvars> current_vars, std::vector<stsclasstype> classtypes){ //handles both print and printl.
    string val = "";
    int ln = *y;
    if (prs[line][0]=='\"'){
        prs[line].erase(prs[line].begin());
        prs[line].pop_back();
        val = prs[line];
    }
    else{
        if (current_vars.size()!=0){
            for (int x = 0; x<=current_vars.size()-1; x++){ //check variables
                if (prs[line]==current_vars[x].name){
                    if (current_vars[x].type=='i') { val = std::to_string(current_vars[x].valint); }
                    else if (current_vars[x].type=='b') { 
                        bool z = current_vars[x].val;
                        if (z==1){ val="true"; }
                        else{ val="false"; }
                    }
                    else if (current_vars[x].type=='j') { //integer array
                        if (prs[line+1]=="["){
                            if (std::stoi(prs[line+2])<=current_vars[x].valsint.size()-1){
                                val=std::to_string(current_vars[x].valsint[std::stoi(prs[line+2])]);
                            }
                            else{ error(6, prs[line+2]); }
                        }
                        else{ error(5, current_vars[x].name); }
                    }
                    else if (current_vars[x].type=='t') { //string array
                        if (prs[line+1]=="["){
                            if (std::stoi(prs[line+2])<=current_vars[x].valsstring.size()-1){
                                val=current_vars[x].valsstring[std::stoi(prs[line+2])];
                            }
                            else{ error(6, prs[line+2]); }
                        }
                        else{ error(5, current_vars[x].name); }
                    }
                    else { val = current_vars[x].valstring; }
                    break;
                }
            }
        }
        if (functions.size()!=0){
            for (int x = 0; x<=functions.size()-1; x++){
                if (prs[line]==functions[x].name){
                    exec(functions[x].linestarted, names, x);
                    if (functions[x].value.type=='s'){
                        val=functions[x].value.valstring;
                    }
                    else if (functions[x].value.type=='b') { 
                        bool z = functions[x].value.val;
                        if (z==1){ val="true"; }
                        else{ val="false"; }
                    }
                    else{
                        val=std::to_string(functions[x].value.valint);
                    }
                    break;
                }
            }
        }
        if (classtypes.size()!=0) {
            for (int i = 0; i<classtypes.size(); i++) {
                if (prs[ln] == classtypes[i].name) {
                    ln++;
                    for (int d = 0; d<classtypes[i].tpe.variables.size(); d++) {
                        if (prs[ln]==classtypes[i].tpe.variables[d].name) {
                            switch (classtypes[i].tpe.variables[d].type) {
                                case 'i': val = std::to_string(classtypes[i].tpe.variables[d].valint);
                                    break;
                                case 's': val = classtypes[i].tpe.variables[d].valstring;
                                    break;
                                case 'b': val = ((classtypes[i].tpe.variables[d].val) ? "true" : "false");
                                    break;
                            }
                        }
                    }
                }
            }
        }
    }
    
    for (int x = 0; x<=val.size(); x++){
        if ((val[x]=='\\') && (val[x+1]=='n')){
            val.pop_back();
            val[x]='\n';
        }
    }

    *y = ln;

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
        char valstring[256];
        std::cin.getline(valstring, 256);
        input.valstring=valstring;
    }
    else if (prs[line]=="bool") {
        input.type = 'b';
        std::cin >> input.val;
    }

    return input;
}