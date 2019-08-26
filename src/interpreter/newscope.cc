#include "../stormscript.h"
#include "sts_interpreter.h"

void newScope() {
	std::vector<stsfunc> _functions = program.thisScope.functions;
	std::vector<stsvars> _variables = program.thisScope.variables;
	std::vector<type> _types = program.thisScope.types;
	std::vector<stsObject> _objects = program.thisScope.objects;

	while ((program.expressions[program.loc].tktype != CLOSEDCURL) && (program.loc < program.expressions.size())) {
		
		switch(program.expressions[program.loc].t) { // don't need to worry about TOKEN and ENDEXPR because they will be handled inside of functions
			case BUILTIN:
				if (program.expressions[program.loc].btn != STSSOCKET) {
					runBuiltin();
					break;
				}
			case UNKNOWN:
				runUnknown();
				break;
		}

		program.loc++;
	}

	program.thisScope.variables.erase(program.thisScope.variables.begin() + _variables.size(), program.thisScope.variables.end());
	program.thisScope.objects.erase(program.thisScope.objects.begin() + _objects.size(), program.thisScope.objects.end());

	_variables = program.thisScope.variables;
	_objects = program.thisScope.objects;

	program.thisScope = scope(_functions, _variables, _types); // reset size back to original
}