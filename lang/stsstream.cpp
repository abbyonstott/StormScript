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