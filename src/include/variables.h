#pragma once
#ifndef VARIABLES_H_
#define VARIABLES_H_

#include "includes.h"
#include "core.h"

class stsvars{
public:
	int valint = 0;
	int length;
	std::vector<stsvars> vals;
	string valstring = "";
	bool val, glob;
	string name;
	char type;

	void assignlist(sts *script, std::vector<stsvars> vars, int *line);
};

#endif