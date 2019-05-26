#include "../include/stormscript.h"
/*
int genrandomintfromrange(sts *s, std::vector<stsvars> vars, int *line) {
    long int ut = static_cast<long int> (time(0)); // cast unix epoch to long int
    int y = *line;
    int range[2]; // range will store the min and max values

    std::vector<string> prs = s->prs;

    srand(ut); // seed rand() with unix epoch

    y+=2;
    
    if (prs[y] == "min:")
        range[0] = std::stoi(s->getval(vars, new int(y+1)).val);
    else if (prs[y] == "max:")
        range[1] = std::stoi(s->getval(vars, new int(y+1)).val);
    
    y+=2;

    if (prs[y] == "min:")
        range[0] = std::stoi(s->getval(vars, new int(y+1)).val);
    else if (prs[y] == "max:")
        range[1] = std::stoi(s->getval(vars, new int(y+1)).val);

    y++;

    *line = y;

    return rand() % range[1] + range[0];
}

bool randombool() {
    long int ut = static_cast<long int> (time(0));
    srand(ut);
    return rand() % 2;
}

*/