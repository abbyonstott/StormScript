#pragma once
#ifndef SCOPE_H_
#define SCOPE_H_

#include "includes.h"
#include "parser.h"

struct scope {
    std::vector<type> types;
    std::vector<stsfunc> functions;
    std::vector<stsvars> variables;
    std::vector<typedvar> typedvars;

    scope(std::vector<stsfunc> f = {}, std::vector<stsvars> v = {}, std::vector<type> t = {}, std::vector<typedvar> V = {}) {
        types = t;
        functions = f;
        variables = v;
        typedvars = V;
    }
};

#endif