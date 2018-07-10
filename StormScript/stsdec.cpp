#include "stsclasses.h"

/*
stsdec.cpp: basic type and function declarations
declare(): variables
*/

string sts::declare(char type, int line){ //variable declarations
    string name = ""; //name
    string val = ""; //value
    string a; //command to compile

    if (type == 'i'){
        for (int y=0; y<=prs[line+1].size();y++){
            if (prs[line+1][y]!=':'){
                name+=prs[line+1][y];
            }
        }
        for (int y=0; y<=prs[line+2].size();y++){
            if (prs[line+2][y]!=';'){
                val+=prs[line+2][y];
            }
        }
        for (int y=0; y<=val.size()-2; y++){
            if (isdigit(val[y])==false){
                error(2, name);
            }
        }
        a = "echo '\tint ";
        const char *c = name.c_str();
        const char *e = " = ";
        const char *d = val.c_str();
        const char *f = ";' >> stscompile/stscomp.cpp";
        a+=c;
        a+=e;
        a+=d;
        a+=f;
    }
    else if (type == 's'){
        for (int y=0; y<=prs[line+1].size();y++){
            if (prs[line+1][y]!=':'){
                name+=prs[line+1][y];
            }
        }
        for (int y=0; y<=prs[line+2].size();y++){
            if (prs[line+2][y]!=';'){
                val+=prs[line+2][y];
            }
        }
        
        a = "echo '\tstd::string ";
        const char *c = name.c_str();
        const char *e = " = ";
        const char *d = val.c_str();
        const char *f = ";' >> stscompile/stscomp.cpp";
        a+=c;
        a+=e;
        a+=d;
        a+=f;
    }

    return a;
}