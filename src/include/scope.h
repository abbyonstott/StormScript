#pragma once
#ifndef SCOPE_H_
#define SCOPE_H_

#include "includes.h"
#include "parser.h"

struct scope {
    std::vector<type> types;
    std::vector<stsfunc> functions;
    std::vector<stsvars> variables;

    scope(std::vector<stsfunc> f = {}, std::vector<stsvars> v = {}, std::vector<type> t = {}) {
        types = t;
        functions = f;
        variables = v;
    }
};

#endif