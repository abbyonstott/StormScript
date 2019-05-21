#include "../include/stormscript.h"

bool condition(sts *program, int *y, std::vector<stsvars> vars) {
    TokenType comparisonType;
    int opLocation;

    if ((program->expressions[*y+1].tktype == IS) || (program->expressions[*y+1].tktype == NOT) || (program->expressions[*y+1].tktype == GREATER) || (program->expressions[*y+1].tktype == GREATEREQ) || (program->expressions[*y+1].tktype == LESS) || (program->expressions[*y+1].tktype == LESSEQ))
        comparisonType = program->expressions[*y+1].tktype; // set comparison type to condition
    else {
        int i = *y;
        
        while ((program->expressions[i].tktype != IS) && (program->expressions[i].tktype != NOT) && (program->expressions[i].tktype != GREATER) && (program->expressions[i].tktype != GREATEREQ) && (program->expressions[i].tktype != LESS) && (program->expressions[i].tktype != LESSEQ))
            i++;

        comparisonType = program->expressions[i].tktype;
        opLocation = i;
    }

    sts prg; // create more isolated expressions to get the value to compare
    
    for (int i = *y; i < opLocation; i++)
        prg.expressions.push_back(program->expressions[i]);

    stsvars comp1 = prg.getval(vars, new int(0));

    prg.expressions = {};
    int l = opLocation;

    for (l = opLocation; (program->expressions[l+1].t != ENDEXPR) && (program->expressions[l+1].tktype != OPENCURL) && (program->expressions[l+1].tktype != TERNARY1); l++)
        prg.expressions.push_back(program->expressions[l]);
    
    *y = l;

    stsvars comp2 = prg.getval(vars, new int(0));
    
    if (comp1.type == comp2.type) {
        switch (program->expressions[*y].tktype) {
            case IS:
                return (comp1.val == comp2.val);
        }
    }
    else
        program->error(9, program->expressions[opLocation+1].contents);
}