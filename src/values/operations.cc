#include "../include/stormscript.h"

bool toBool(string s) {
    return (s == "true");
}

stsvars findVar(std::vector<stsvars> vars, string query) {
    for (int i = 0; i < vars.size(); i++) {
        if (vars[i].name == query)
            return vars[i];
    }
}

bool isvar(std::vector<stsvars> * pvars, string query, int *num) {
    bool isvar = false;

    for (int i = 0; i < pvars->size() && !isvar; i++) {
        isvar = (pvars->at(i).name == query);
        if (isvar)
            *num = i;
    }

    return isvar;
}

string striplit(string line) {
    line.pop_back();
    line.erase(line.begin());

    return line;
}

bool isint(string s) {
    for (int i = 0; i < s.size(); i++) {
        if ((std::isdigit(s[i])) || ((s[i]=='-') && (std::isdigit(s[i]))))
            return true;
        else
            return false;
    }

    return false;
}

void scopedown(int *x, std::vector<string> prs) {
    int y = *x;
    int e = 1;
    y++;

    while (e != 0) {
        if ((prs[y] == "if") || (prs[y] == "while") || (prs[y] == "for"))
            e++;
        else if (prs[y] == "else") {
            e++;
            if (prs[y+1] == "if")
                y++;
        }
        else if (prs[y] == "}")
            e--;
        y++;
    }
    y--;

    *x = y;
}