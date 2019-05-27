#pragma once
#ifndef VARIABLES_H_
#define VARIABLES_H_

#include "includes.h"
#include "core.h"

class stsvars {
public:
	char type; // Later on, this "type" value should be replaced with a Value enum type so that it can be set to INTEGER, STRING, STS_BOOL
	string val;

	std::vector<stsvars> vals;

	int length;
	string name;

	void assignlist(sts *script, std::vector<stsvars> vars, int *line);
};

#endif