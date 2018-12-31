#pragma once
#ifndef STSCLASSES_H_
#define STSCLASSES_H_

#if defined(_WIN32)
#define PLATFORM "Windows"
#else
#define PLATFORM "other"
#endif

#include "includes.h"


#include "core.h"


#include "classes.h"


#include "variables.h"


#include "functions.h"

using std::cout;

// for the most part, it is a better idea to use functions outside of the sts class

string striplit(string line);
bool condition(sts *program, int *ln, std::vector<stsvars> vars);
bool isint(string s);
bool toBool(string s);

#endif