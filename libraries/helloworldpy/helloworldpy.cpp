#include <iostream>

int main(int argc, char *argv[]){
    std::string cmd1 = "helloworldstslib.py ";
    cmd1+=" ";
    cmd1+=argv[1];
    system(cmd1.c_str());
    return 0;
}