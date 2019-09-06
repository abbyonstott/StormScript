#include "../stormscript.h"
#include "sts_values.h"

bool condition() {
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
	int _loc = program.loc;

	int i = program.loc;
	
	while ((program.expressions[i].tktype != IS) && (program.expressions[i].tktype != NOT) && (program.expressions[i].tktype != GREATER) && (program.expressions[i].tktype != GREATEREQ) && (program.expressions[i].tktype != LESS) && (program.expressions[i].tktype != LESSEQ))
		i++;

	comparisonType = program.expressions[i].tktype;
	opLocation = i;

	program_t program_old = program; // create more isolated expressions to get the value to compare
	program.expressions = {};
	program.loc = 0;
	program.looping = false;

	for (int i = program_old.loc; i < opLocation; i++)
		program.expressions.push_back(program_old.expressions[i]);

	stsvars comp1 = getval();

	program.expressions = {};
	int l = opLocation;

	for (l = opLocation+1; (program_old.expressions[l].t != ENDEXPR) && (program_old.expressions[l].tktype != OPENCURL) && (program_old.expressions[l].tktype != TERNARY1); l++)
		program.expressions.push_back(program_old.expressions[l]);
	
	program_old.loc = l;

	program.loc = 0;
	stsvars comp2 = getval();

	program = program_old;
	
	if (comp1.type == comp2.type) {
		switch (comparisonType) {
			case IS: return (comp1.val == comp2.val);
			case NOT: return (comp1.val != comp2.val);
			case GREATER: 
				if ((comp1.type == INTEGER) && (comp2.type == INTEGER)) return (std::stoi(comp1.val) > std::stoi(comp2.val));
				else if (comp1.type != INTEGER) error(2, program.expressions[_loc].contents); // give error with first expression
				else if (comp2.type != INTEGER) error(2, program.expressions[opLocation+1].contents); // give error with second expression
				break;
			case LESS:
				if ((comp1.type == INTEGER) && (comp2.type == INTEGER)) return (std::stoi(comp1.val) < std::stoi(comp2.val));
				else if (comp1.type != INTEGER) error(2, program.expressions[_loc].contents); // give error with first expression
				else if (comp2.type != INTEGER) error(2, program.expressions[opLocation+1].contents); // give error with second expression
				break;
			case GREATEREQ: 
				if ((comp1.type == INTEGER) && (comp2.type == INTEGER)) return (std::stoi(comp1.val) >= std::stoi(comp2.val));
				else if (comp1.type != INTEGER) error(2, program.expressions[_loc].contents); // give error with first expression
				else if (comp2.type != INTEGER) error(2, program.expressions[opLocation+1].contents); // give error with second expression
				break;
			case LESSEQ:
				if ((comp1.type == INTEGER) && (comp2.type == INTEGER)) return (std::stoi(comp1.val) <= std::stoi(comp2.val));
				else if (comp1.type != INTEGER) error(2, program.expressions[_loc].contents); // give error with first expression
				else if (comp2.type != INTEGER) error(2, program.expressions[opLocation+1].contents); // give error with second expression
				break;
		}
	}
	else
		error(2, program.expressions[opLocation+1].contents);

	return 0;
}
