#pragma once
#ifndef TYPE_H_
#define TYPE_H_

#include "includes.h"
#include "core.h"

class type {
public:
    string name;

    std::vector<stsvars> objects;
    std::vector<stsfunc> methods;
};

class typedvar {
public:
    string name;

    type Parent;

    typedvar(type _Parent = type()) {
        Parent = _Parent;
    }
};

#endif