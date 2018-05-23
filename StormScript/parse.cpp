#include "stsclasses.h"

string cmd(string line){
    string full;
    int x = 0;

    while ((line[x]!=' '))
    {
        if ((line[x]=='{') || (line[x]==';')) {break;}
        full += line[x];
        x++;
    }

    return full;
}

void sts::readline(string prg[], int psize) {
    std::vector<string> ln(psize); // create vector of line commands

    for (int line = 0; line<=psize-1; line++) {
        ln[line]=cmd(prg[line]);
    }

    for (int line = 0; line<=psize-1; line++) {
        if (ln[line]=="do") {
            stsdo();
        }
    }
}