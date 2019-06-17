#include "../include/stormscript.h"

stsvars sts::readfile(int *y) {
    stsvars v;
    v.type = 's';

    *y+= 1;

    std::ifstream file;
    string contents;
    string name = getval(y).val;

    file.open(name);

    if (file.fail()) 
		error(0, name);

    char c = file.get();

    while (file.good()) {
        contents += c;
        c = file.get();
    }

    file.close();

    v.val = contents;

    return v;
}

void sts::writefile(int *y) {
    *y += 1;
    std::ofstream file;
    string name = getval(y).val;

    file.open(name);

    *y += 1;
    string contents = getval(y).val;

    file.write(contents.c_str(), contents.size());
    file.close();

    *y += 1;
}