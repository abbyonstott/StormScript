#pragma once
#ifndef STS_VALUES_H_
#define STS_VALUES_H_

#include "../stormscript.h"

void ifs();

void runfunc(int num);

// find is overloaded to allow finding any of the main types easily
bool find(std::vector<stsvars> vars, string query, int *num);
bool find(std::vector<stsfunc> functions, string query, int *num);
bool find(std::vector<type> types, string query, int *num);
bool find(std::vector<stsObject> vars, string query, int *num);

// random functions
int genrandomintfromrange();
bool randombool();


// stsdec functions
void declareFunc();
void define();

bool condition();

#endif // STS_VALUES_H_