#pragma once
#ifndef INCLUDES_H_
#define INCLUDES_H_

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <memory>
#include <random>
#include <time.h>
#include <stdio.h>

/*
Let's forward declare these classes for the files that use them
*/
class sts;
class stsvars;
class stsfunc;

using std::string;
using std::cout;
// I have to include this for cmake

#include "../StormScriptconfig.h"

#endif