#include "../include/core.h"

void sts::readfile(int y, stsvars *v) {
    v->type = 's';
    v->glob = false;

    std::ifstream file;
    string contents;
    string name = striplit(prs[y]);

    file.open(name);

    if (file.fail()) 
		error(11, name);

    char c = file.get();

    while (file.good()) {
        contents += c;
        c = file.get();
    }

    file.close();

    v->val = contents;
}

void sts::writefile(int y) {
    std::ofstream file;
    string name = striplit(prs[y]);
    file.open(name);
    file.write(striplit(prs[y+1]).c_str(), striplit(prs[y+1]).size());
    file.close();
}