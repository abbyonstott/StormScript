#include "../include/stormscript.h"

int genrandomintfromrange(std::vector<string> prs, int *line) {
    long int ut =  static_cast<long int> (time(0)); // cast unix epoch to long int
    int y = *line;
    int range[2]; // range will store the min and max values

    srand(ut); // seed rand() with unix epoch

    y+=2;
    
    if (prs[y] == "min:")
        range[0] = std::stoi(prs[y+1]);
    else if (prs[y] == "max:")
        range[1] = std::stoi(prs[y+1]);
    
    y+= 2;

    if (prs[y] == "min:")
        range[0] = std::stoi(prs[y+1]);
    else if (prs[y] == "max:")
        range[1] = std::stoi(prs[y+1]);

    y+= 2;

    *line = y;

    return rand() % range[1] + range[0];
}