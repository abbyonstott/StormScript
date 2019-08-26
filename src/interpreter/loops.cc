#include "../stormscript.h"
#include "../values/sts_values.h"
#include "sts_interpreter.h"

void whileloop() {
	program.loc += 1;
	program_t program_old = program;

	int n = program.loc;
	program.looping = true;

	while (toBool(getval().val)) {
		newScope();

		if (!program.looping) break; // looping should only be false in the case of a break;

		n = program.loc; // set n back to y to repeat
	}

	while (program.expressions[program.loc].tktype != OPENCURL) program.loc++;
	program.loc += 1;

	program_old.loc = program.loc;
	program_old.thisScope = program.thisScope; // get new versions of variables
	program = program_old;
	scopedown();
}


void forloop() {
	program.loc += 1;
	program_t program_old = program;

	bool foreach = (program.expressions[program.loc+1].btn == STSIN);
	program.looping = true;

	if (foreach) {
		stsvars root;
		string name;
		int rootsize;
		name = program.expressions[program.loc].contents;
		
		program.loc += 2;

		// grab variable listed on 3rd argument of for loop
		int rootnum;
		find(program.thisScope.variables, program.expressions[program.loc].contents, &rootnum);
		root = program.thisScope.variables[rootnum];
		
		program.loc += 1;

		switch (root.type) {
			case 's':
			case 'l': rootsize = root.length;
				break;
			case 'i':
			case 'b':
				error(2, root.name);
		}


		for (int i = 0; i < rootsize; i++) {
			stsvars placeholder;

			if (root.type == 'l')
				placeholder = root.vals[i];
			else {
				placeholder.val = std::to_string(root.val[i]);
				placeholder.length = 1;
				placeholder.type = 's';
			}
			placeholder.name = name;

			program.thisScope.variables.push_back(placeholder);

			newScope();

			program.thisScope.variables.pop_back();

			if (!program.looping) break;
		}

		program.loc += 1;

	}
	else {
		int r = std::stoi(getval().val);
		program.loc += 1;
		
		if (r <= 0)
			error(4, std::to_string(r));

		for (int i = 0; i < r; i++) {
			newScope();   
			if (!program.looping) break;
		}

		program.loc += 1;
	}


	program_old.loc = program.loc;
	program_old.thisScope = program.thisScope;
	program = program_old;

	scopedown();
}
