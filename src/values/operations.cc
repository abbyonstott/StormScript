#include "../include/stormscript.h"

bool toBool(string s) {
    return (s == "true");
}


string striplit(string line) {
    line.pop_back();
    line.erase(line.begin());

    return line;
}

bool isint(string s) {
    for (int i = 0; i<s.size(); i++) {
        if ((std::isdigit(s[i])) || (s[i]=='-'))
            return true;
        else
            return false;
    }
    return false;
}