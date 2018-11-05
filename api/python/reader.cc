#include <iostream>

using std::string;
using std::cout;
using std::endl;

int main(int argc, char const *argv[])
{
    string cmd = "test.py {\\'command\\':";
    if (argc>2) { cmd+="{"; }
    string args[argc];
    for (int i = 1; i<argc; i++) {
        args[i-1]=argv[i];
    }
    for (int i = 0; i<argc-1; i++) {
        string val = args[i];

        if (args[i].back()==':') {
            cmd+="{";
            val.pop_back();
        }
        if (i>0) {
            if (args[i-1].back()!=':') {
                cmd+="\\'";  
            } 
            else{
                args[i] = "\\\""+val+"\\\"";
                val = args[i];
            }
        }
        else {
            cmd+="\\'";  
        }
        cmd+=val;

        if (i>0) {
            if (args[i-1].back()==':') {
                cmd+="}";
            }
            else{
                cmd+=((args[i].back()==':') ? "\\':" : "\\'");
            }
            if (i==argc-2){
                cmd+="]";
            }
            else if (args[i-1].back()==':') {
                cmd+=",";
            }
        }
        else if (argc>i+2){
            cmd+="\\':[";
        }
        else{
            cmd+="\\'";
        }
    }
    if (argc>2) { cmd+="}"; }
    cmd += "}";
    
    system(cmd.c_str());

    return 0;
}
