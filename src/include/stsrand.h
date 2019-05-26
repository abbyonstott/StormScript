#pragma once
#ifndef STSRAND_H_
#define STSRAND_H_

#include "includes.h"

#include "variables.h"

int genrandomintfromrange(sts *s, std::vector<stsvars> *vars, std::vector<stsfunc> functions, int *line);
bool randombool();

#endif