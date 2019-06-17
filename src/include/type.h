#pragma once
#ifndef TYPE_H_
#define TYPE_H_

#include "includes.h"
#include "core.h"

class type {
    string name;

    std::vector<stsvars> objects;
    std::vector<stsfunc> methods;
};

#endif