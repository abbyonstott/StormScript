#pragma once
#ifndef STSCLASSES_H_
#define STSCLASSES_H_

#if (defined(_WIN32)) || (defined(__MINGW32__))
#define PLATFORM 1
#include <windows.h>
#else
#define PLATFORM 0
#include <unistd.h>
#endif
/*
NOTE:
Place All StormScript headers here separated by 2 lines.
*/
#include "includes.h"


#include "core.h"


#include "variables.h"


#include "functions.h"


#include "type.h"


#include "stsrand.h"


#include "scope.h"

using std::cout;

// for the most part, it is a better idea to use functions outside of the sts class

string striplit(string line);
bool condition(sts *program, int *y);
bool isint(string s);
bool toBool(string s);

// find is overloaded to allow finding any of the main types easily
bool find(std::vector<stsvars> * pvars, string query, int *num);
bool find(std::vector<stsfunc> functions, string query, int *num);
bool find(std::vector<type> types, string query, int *num);
bool find(std::vector<typedvar> vars, string query, int *num);

stsvars findVar(std::vector<stsvars> vars, string query);

#endif
