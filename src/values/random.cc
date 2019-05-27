#include "../include/stormscript.h"

int genrandomintfromrange(sts *s, std::vector<stsvars> *vars, std::vector<stsfunc> functions, int *line) {
    long int ut = static_cast<long int> (time(NULL)); // cast unix epoch to long int
    int y = *line;
    int range[2]; // range will store the min and max values

    y++;

    std::vector<expression> expressions = s->expressions;

    srand(ut); // seed rand() with unix epoch

    range[0] = std::stoi(s->getval(vars, functions, &y).val);
    y++;
    range[1] = std::stoi(s->getval(vars, functions, &y).val);

    *line = y;

    return rand() % (range[1] + 1 - range[0]) + range[0];
}

bool randombool() {
    long int ut = static_cast<long int> (time(0));
    srand(ut);
    return rand() % 2;
}