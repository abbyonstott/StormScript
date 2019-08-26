#include "../stormscript.h"
#include "../interpreter/sts_interpreter.h"

void runfunc(int num) {
	program_t program_old = program;

	std::vector<stsvars> _variables = program.thisScope.variables;

	program_old.thisScope.variables.insert(program_old.thisScope.variables.end(), 
		program_old.thisScope.functions.at(num).args.begin(), program_old.thisScope.functions.at(num).args.end());

	program.function = num;
	program.expressions = program_old.thisScope.functions.at(num).contents;

	int argbegin = _variables.size(); 

	if (program_old.thisScope.functions.at(num).args.size() > 0) {
		if (program_old.expressions[program_old.loc+1].tktype != ARROW)
			error(5, program_old.thisScope.functions.at(num).name);
		else {
			program_old.loc += 2;

			int argon = 0;
			
			while (true) {
				program_t _prog = program;
				program = program_old;

				program.thisScope.variables[argbegin + argon] = getval();
				
				program_old = program;
				program = _prog;

				program_old.thisScope.variables[argbegin + argon].name = program_old.thisScope.functions.at(num).args[argon].name;

				program_old.loc += 1;
				if (program_old.expressions[program_old.loc].t == ENDEXPR) break;
				else if (program_old.expressions[program_old.loc].tktype == COMMA) {
					program_old.loc++;
					argon += 1;
				}
			}
		}
	}

	program.thisScope = program_old.thisScope;
	program.loc = 0;
	newScope();

	program_old.thisScope = program.thisScope;
	program_old.thisScope.variables.erase(program_old.thisScope.variables.begin() + _variables.size(), program_old.thisScope.variables.end());

	program = program_old;
}
