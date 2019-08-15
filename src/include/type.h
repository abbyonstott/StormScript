#pragma once
#ifndef TYPE_H_
#define TYPE_H_

#include "includes.h"
#include "core.h"

class type {
public:
	string name;

	std::vector<stsvars> members;
	std::vector<stsfunc> methods;
};

class stsObject: public type {
public:
	string Parentname;

	stsObject(const type &_Parent = type()) {
		Parentname = _Parent.name;
		members = _Parent.members;
		methods = _Parent.methods;
	}
};

#endif