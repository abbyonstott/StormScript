#include "stsclasses.h"

string sts::out(string str)
{
    if (str[0]=='\"') {
        str[0]='\0';
        str[str.size()-1]='\0';
        return str;
    }
    else { 
        for (int x = 0; x<=varnames.size(); x++) { 
            if (str==varnames[x]){
                str=vars[x];
                return str;
            } 
        }
    }
    error(0,str);
}