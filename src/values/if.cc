#include "../stormscript.h"
#include "../interpreter/sts_interpreter.h"
#include "sts_values.h"

void ifs() {
	/*
	if statements are pretty easy to parse as they are always formated like this
	BUILTIN |    VALUE/COMPARISON*    |   TOKEN
	--------|-------------------------|-----------
	if      |          var            |    {

	*The VALUE/EXPRESSION can be a bool literal, a variable, or a comparison. This is not determined here, but later in getval()
	*/

	program_t program_old = program; // store old program values for reuse
	program_old.loc++;

	program.loc = 0;
	program.expressions.clear();

	while (program_old.expressions[program_old.loc].tktype != OPENCURL) {
		program.expressions.push_back(program_old.expressions[program_old.loc]);
		program_old.loc++;
	}

	program.expressions.push_back(program_old.expressions[program_old.loc]);
	bool expr = toBool(getval().val);

	program = program_old;

	if (expr) {
		program.loc++;
		newScope();
		program.loc++; // get out of scope to check for else
	}
	else { 
		program.loc++;
		
		scopedown();

		if (program.expressions[program.loc+1].btn == ELSE) {
			/* 
			This works because it parses the expression after else. 
			This would be { or OPENCURL if it is a standard else statement and IF it it were an else if statement.
			*/
			program.loc += 2;
			newScope();
		}
	}

	if (program.expressions[program.loc].btn == ELSE) {
		if (program.expressions[program.loc+1].btn == IF)
			while (program.expressions[program.loc - 1].tktype != OPENCURL) program.loc++;
		else program.loc += 2;

		scopedown();
	}
	else if (expr) // subtract one if expression is true to compensate for next line of program
		program.loc -= 1;
}
