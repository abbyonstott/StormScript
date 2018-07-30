#include "stsclasses.h"

/*
stsstream.cpp: all of the basic input and output streams.
*/

string sts::out(int line){
    string val = "";

    prs[line+1].pop_back();
    val = prs[line+1];

    string a = "echo '\tstd::cout << "; 
    string c = " << std::endl;' >> stscompile/stscomp.cpp";
    a+=val.c_str();
    a+=c.c_str();

    return a;
}