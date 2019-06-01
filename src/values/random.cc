#include "../include/stormscript.h"

int genrandomintfromrange(sts *s, std::vector<stsvars> *vars, std::vector<stsfunc> functions, int *line) {
    long int ut = static_cast<long int> (time(NULL)); // cast unix epoch to long int
    int y = *line;
    int range[2]; // range will store the min and max values

    y++;

    std::vector<expression> expressions = s->expressions;

    std::random_device randomd;

    std::mt19937_64 generate(randomd());

    range[0] = std::stoi(s->getval(vars, functions, &y).val);
    y++;
    range[1] = std::stoi(s->getval(vars, functions, &y).val);

    *line = y;

    std::uniform_int_distribution<> dis(range[0], range[1]);

    return dis(generate);
}

bool randombool() {
    std::random_device randomd;

    std::mt19937_64 generate(randomd());
    std::uniform_int_distribution<> dis(0, 1);
    return dis(generate);
}