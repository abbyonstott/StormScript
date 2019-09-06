#include "../stormscript.h"
#include "sts_values.h"

void declareFunc() {
	program.thisScope.functions.push_back(stsfunc());

	program.loc += 1;

	program.thisScope.functions.back().name = program.expressions[program.loc].contents;

	program.loc += 1;

	if (program.expressions[program.loc].tktype == ARROW) {
		program.loc += 1;

		while (true) {
			program.thisScope.functions.back().args.push_back(stsvars());
			program.thisScope.functions.back().args.back().name = program.expressions[program.loc].contents;
			program.loc += 1;

			if (program.expressions[program.loc].tktype == OPENCURL) break;
			else if (program.expressions[program.loc].tktype == COMMA) program.loc += 1;
		}
		
	}
	program.loc += 1;

	int endreq = 1;

	while (endreq != 0)  {
		if (program.expressions[program.loc].tktype == OPENCURL) endreq += 1;
		else if (program.expressions[program.loc].tktype == CLOSEDCURL) endreq -= 1;

		program.thisScope.functions.back().contents.push_back(program.expressions[program.loc]);

		program.loc += 1;
	}

	program.thisScope.functions.back().contents.pop_back(); // remove last line as it is just a closed curl
	program.loc -= 1;
}

std::vector<stsvars> 
listgen() {
	std::vector<stsvars> values;
	program.loc++;

	while (program.expressions[program.loc-1].tktype != CLOSEDBRACKET) {
		values.push_back(getval());
		program.loc+= 2;
	}
	
	program.loc--;

	return values;
}


void define() { //variable declarations
	int num = program.thisScope.variables.size();
	string name = program.expressions[program.loc].contents;

	if (find(program.thisScope.variables, name, &num)) {
		/*
		* If already defined this changes the value of 
		* the variable
		*/
		program.loc += 2;
		if (program.thisScope.variables.at(num).type != 'l')
			program.thisScope.variables.at(num) = getval();
		else 
			program.thisScope.variables.at(num).vals = listgen();
		program.thisScope.variables.at(num).name = name;
	}
	else {
		program.thisScope.variables.push_back(stsvars());
		program.loc += 2;

		if (program.expressions[program.loc].tktype != OPENBRACKET)
			program.thisScope.variables.back() = getval();
		else {
			program.thisScope.variables.back().type = LIST;
			program.thisScope.variables.back().vals = listgen();
		}

		program.thisScope.variables.back().name = name;
	}

	switch (program.thisScope.variables.at(num).type) {
		case STRING:
			program.thisScope.variables.at(num).length = program.thisScope.variables.at(num).val.size();
			break;
		case LIST:
			program.thisScope.variables.at(num).length = program.thisScope.variables.at(num).vals.size();
			break;
	}
	while (program.expressions[program.loc].t != ENDEXPR) program.loc += 1;
}