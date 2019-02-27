#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <memory>
#include <random>
#include <time.h>

/*
Let's forward declare these classes for the files that use them
*/
class sts;
class stsvars;
class stsclass;
class stsclasstype;
class stsfunc;

using std::string;
using std::cout;
// I have to include this for cmake

#include "../StormScriptconfig.h"