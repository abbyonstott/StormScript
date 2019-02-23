#pragma once
#ifndef VARIABLES_H_
#define VARIABLES_H_

#include "includes.h"
#include "core.h"

class stsvars {
public:
	char type;
	string val;

	std::vector<stsvars> vals;

	int length;
	bool glob = false;
	string name;

	void assignlist(sts *script, std::vector<stsvars> vars, int *line);
};

#endif // VARIABLES_H_