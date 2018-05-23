#include "stsclasses.h"

void sts::out(string str)
{
    if (str[0]=='\"') {
        str[0]='\0';
        str[str.size()-1]='\0';
    }
    else {error(0,str);}

	cout << str << endl;
}