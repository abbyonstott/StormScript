#include <iostream>

int main(int argc, char *argv[]){
    std::string command = "webpysts.py 127.0.0.1:9000 ";
    command+=argv[1];
    if (argc==3){
        std::string  x = " ";
        command+=x.c_str();
        command+=argv[2];
    }
    system(command.c_str());
    return 0;
}