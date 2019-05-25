#pragma once
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "includes.h"
#include "core.h"
#include "variables.h"
#include "parser.h"
#include "classes.h"

class stsfunc:public stsvars{
public:
	int linestarted;
	bool classmethod = false;
	stsvars value;
	string cof;
	string modname = "main";
	stsclasstype cval;
	char valtype;
	std::vector<expression> contents;
	std::vector<stsvars> args;
};

#endif