#include "stsclasses.h"

/*
stsdec.cpp: basic type and function declarations
declare(): variables
fdeclare(): declare functions
checkiffunction(): returns a boolean of if the name is a function or not
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

string sts::fdeclare(int line){
    // declares function
    string name;
    int n = 0;
    while (prs[line+1][n]!='{'){
        name+=prs[line+1][n];
        n++;
    }
    // add echo to cmd1 (the command that system() is executing)
    string cmd1 = "echo 'auto ";
    string cmd2 = "(){' >> stscompile/stscomp.cpp";
    cmd1 += name.c_str();
    cmd1 += cmd2.c_str();
    system(cmd1.c_str());

    return name;
}

int sts::checkiffunction(string line){
    int fnum = -1; //returns -1 if it is not a function
    string cmd;

    for (int x = 0; x<=line.size(); x++){
        if (line[x]==';'){
            break;
        }
        cmd+=line[x];
    }

    for (int x = 0; x<=functions.size(); x++){
        if (functions[x]==cmd){
            fnum = x;
        }
    }

    return fnum;
}