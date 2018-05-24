#include "stsclasses.h"

void sts::decvar(string contents, char type){
    if (type=='s'){
        for (int x = 0; x<=contents.size(); x++) {
            if (contents[x]=='\"') { contents[x] = '\0'; }
        }
        vars.resize(vars.size()+1);
        vars[vars.size()-1]=contents;
    }
}