#include "../include/stormscript.h"

bool condition(sts *program, int *y) {
    /*
    Comparisons are formatted like this:
    VALUE/UNKNOWN |               TOKEN                  |VALUE/UNKNOWN
    -----------------------------------------------------|-------------
    var           | is/not/greater/less/greatereq/lesseq | var
    
    The right and left hand values can also contain subscripts, in which case they would look more like this:
    UNKNOWN | TOKEN | VALUE/UNKNOWN | TOKEN
    var     |  [    |     INTEGER   |   ]
    */
    tokenType comparisonType;
    int opLocation;
    int oldy = *y;

    // The below if statement checks if the value contains a subscript or not by determining the location of the comparison operator
    if ((program->expressions[*y+1].tktype == IS) || (program->expressions[*y+1].tktype == NOT) || (program->expressions[*y+1].tktype == GREATER) || (program->expressions[*y+1].tktype == GREATEREQ) || (program->expressions[*y+1].tktype == LESS) || (program->expressions[*y+1].tktype == LESSEQ)) {
        comparisonType = program->expressions[*y+1].tktype; // set comparison type to condition
        opLocation = *y+1;
    }
    else {
        int i = *y;
        
        while ((program->expressions[i].tktype != IS) && (program->expressions[i].tktype != NOT) && (program->expressions[i].tktype != GREATER) && (program->expressions[i].tktype != GREATEREQ) && (program->expressions[i].tktype != LESS) && (program->expressions[i].tktype != LESSEQ))
            i++;

        comparisonType = program->expressions[i].tktype;
        opLocation = i;
    }

    sts prg; // create more isolated expressions to get the value to compare
    prg.thisScope = program->thisScope;

    for (int i = *y; i < opLocation; i++)
        prg.expressions.push_back(program->expressions[i]);


    stsvars comp1 = prg.getval(new int(0));

    prg.expressions = {};
    int l = opLocation;

    for (l = opLocation+1; (program->expressions[l].t != ENDEXPR) && (program->expressions[l].tktype != OPENCURL) && (program->expressions[l].tktype != TERNARY1); l++)
        prg.expressions.push_back(program->expressions[l]);
    
    *y = l;

    stsvars comp2 = prg.getval(new int(0));
    
    if (comp1.type == comp2.type) {
        switch (comparisonType) {
            case IS: return (comp1.val == comp2.val);
            case NOT: return (comp1.val != comp2.val);
            case GREATER: 
                if ((comp1.type == 'i') && (comp2.type == 'i')) return (std::stoi(comp1.val) > std::stoi(comp2.val));
                else if (comp1.type != 'i') program->error(2, program->expressions[oldy].contents); // give error with first expression
                else if (comp2.type != 'i') program->error(2, program->expressions[opLocation+1].contents); // give error with second expression
                break;
            case LESS:
                if ((comp1.type == 'i') && (comp2.type == 'i')) return (std::stoi(comp1.val) < std::stoi(comp2.val));
                else if (comp1.type != 'i') program->error(2, program->expressions[oldy].contents); // give error with first expression
                else if (comp2.type != 'i') program->error(2, program->expressions[opLocation+1].contents); // give error with second expression
                break;
            case GREATEREQ: 
                if ((comp1.type == 'i') && (comp2.type == 'i')) return (std::stoi(comp1.val) >= std::stoi(comp2.val));
                else if (comp1.type != 'i') program->error(2, program->expressions[oldy].contents); // give error with first expression
                else if (comp2.type != 'i') program->error(2, program->expressions[opLocation+1].contents); // give error with second expression
                break;
            case LESSEQ:
                if ((comp1.type == 'i') && (comp2.type == 'i')) return (std::stoi(comp1.val) <= std::stoi(comp2.val));
                else if (comp1.type != 'i') program->error(2, program->expressions[oldy].contents); // give error with first expression
                else if (comp2.type != 'i') program->error(2, program->expressions[opLocation+1].contents); // give error with second expression
                break;
        }
    }
    else {
        program->error(2, program->expressions[opLocation+1].contents);
    }

    return 0;
}
