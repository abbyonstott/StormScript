#pragma once
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "includes.h"
#include "core.h"
#include "variables.h"
#include "classes.h"

class stsfunc:public stsvars{
public:
	int linestarted; // line funcion code starts, not line "func" keyword is used
	bool classmethod = false;
	stsvars value;
	string cof;
	string modname = "main";
	stsclasstype cval;
	char valtype;
	std::vector<stsvars> args;
};

#endif