#include "stsclasses.h"

/*
stsstream.cpp: all of the basic input and output streams.
*/

string sts::out(int line){
    string name = "";
    string val = "";
    for (int y=0; y<=prs[line+1].size();y++){
        if (prs[line+1][y]!=';'){
            val+=prs[line+1][y];
        }
    }

    string a = "echo '\tstd::cout << "; 
    const char *c = " << std::endl;' >> stscompile/stscomp.cpp";
    a+=val.c_str();
    a+=c;

    return a;
}

string sts::in(int line){
    string cmd1 = "echo '\tstd::cin >> ";
    string cmd2 = ";' >> stscompile/stscomp.cpp";
    cmd1+=prs[line].c_str();
    cmd1+=cmd2.c_str();
    
    return cmd1;
}