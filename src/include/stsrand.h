#pragma once
#ifndef STSRAND_H_
#define STSRAND_H_

#include "includes.h"

#include "variables.h"

int genrandomintfromrange(sts *s, std::vector<stsvars> vars, int *line);
bool randombool();

#endif