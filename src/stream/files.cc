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