#include "stsclasses.h"

string sts::runlibfunc(string name, int *line, std::vector<stsvars> vars) {
    int y = *line;
    string cmd1;
    string cmd0 = "echo `"+name;
    if (PLATFORM=="Windows"){
        cmd1 = "stslib.exe ";
    }
    else{
        cmd1 = ".stslib ";
    }
    cmd0+=cmd1.c_str();
    cmd0+=prs[y].c_str();
    y++;
    
    if (prs[y]=="=>") {
        y++;

        while (prs[y]!=";") {
            cmd0+=" ";
            if (prs[y].back()!=':') {
                cmd0+="\'";
                cmd0+=getval(vars, &y).valstring;
                cmd0+="\'";
            }
            else {
                cmd0+=prs[y].c_str();
            }
            y++;
        }
        y--;
    }
    cmd0 += "` >> output.log";
    system(cmd0.c_str());


    std::ifstream command;
    command.open("./output.log");
    
    string output;
    
    while (!command.eof()) {
        output.push_back(command.get());
    }

    command.close();
    system("rm output.log");
    output.pop_back();
    output.pop_back();

    *line = y;
    return output;
}