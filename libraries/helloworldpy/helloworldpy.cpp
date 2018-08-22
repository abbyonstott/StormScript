#include <iostream>

#if defined(_WIN32)
#define PLATFORM "Windows"
#else
#define PLATFORM "other"
#endif

int main(int argc, char *argv[]){
    std::string cmd1;
    if (PLATFORM == "Windows"){
        cmd1 = "helloworldstslibwin.py ";
    }
    else{
        cmd1 = "helloworldstslib.py ";
    }
    cmd1+=" ";
    cmd1+=argv[1];
    system(cmd1.c_str());
    return 0;
}