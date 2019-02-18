#include "../include/stormscript.h"

std::vector<string> readmod(string name) {
    sts s;
    std::ifstream f;

    f.open(name + ".sts");
    string contents;

    char c = f.get();

    if (f.fail()) 
		s.error(11, name+".sts");

    while (f.good()) {
        contents += c;
        c = f.get();
    }
    
    f.close();

    s.prg.resize(s.prg.size() + 1);

    for (int i = 0; i < contents.size(); i++) {
        if (contents[i] == '\n') {
            s.prg.resize(s.prg.size() + 1);
        }
        else {
            s.prg.back() += contents[i];
        }
    }

    return s.parse(s.prg);
}