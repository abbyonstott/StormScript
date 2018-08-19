#include <iostream>

using std::cout;
using std::endl;
using std::string;

int main(int argc, char *argv[]){
    string cmd1 = "out";
    if (argv[1]==cmd1){
        cout << "Hello, World!" << endl;
    }
    return 0;   
}