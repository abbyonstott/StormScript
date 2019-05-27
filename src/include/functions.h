#pragma once
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "includes.h"
#include "core.h"
#include "variables.h"
#include "parser.h"

class stsfunc:public stsvars{
public:
	std::vector<expression> contents;
	std::vector<stsvars> args;
};

#endif