#include "../stormscript.h"
#include "../sts_files.h"
#include "sts_interpreter.h"

// specific headers
#include "../parser/sts_parser.h"
#include "../stream/sts_stream.h"
#include "../values/sts_values.h"
#include "../type/sts_type.h"
#include "../networking/networking.h"

void runBuiltin() {
	bool l;

	switch (program.expressions[program.loc].btn) {
		case PRINT: 
		case PRINTL:
			l = (program.expressions[program.loc].btn == PRINTL); // if printl
			while (program.expressions[program.loc].t != ENDEXPR) {
				cout << print();

				if (program.expressions[program.loc+1].tktype == COMMA) program.loc += 1; // we don't need to add 2 because print() automatically adds 1 to the line counter
			}

			if (l) cout << '\n';
			break;
		case STSIN: 
			program.thisScope.variables.push_back(in());
			break;
		case IF:
			ifs();
			break;
		case FUNCTION:
			declareFunc();
			break;
		case RETURN:
			if (program.function > -1) {
				program.loc++;
				program.thisScope.functions.at(program.function).val = getval().val;
				program.thisScope.functions.at(program.function).type = getval().type;
				program.loc = program.expressions.size(); // return always exits scope
				program.loc--;
			} 
			else error(7, "");
			
			break;
		case WAIT:
			wait();
			break;
		case WRITE:
			writefile();
			break;
		case WHILE:
			whileloop();
			break;
		case FOR:
			forloop();
			break;
		case SYSTEM:
			sys();
			break;
		case TYPE:
			declareType();
			break;
		case BREAK:
			if (program.looping) {
				scopedown();
				program.looping = false;
			}
			else error(6, "");
			break;
		case MODULE:
			/*
			* modules are automatically imported during the error check before runtime
			* all we need to do here is to move on to the next expression
			*/
			while (program.expressions[program.loc].t != ENDEXPR) program.loc += 1;
			break;
		case EXIT:
			exit(0);
	}
}

void runUnknown() {
	int fnum;
	bool shouldbreak;

	switch (program.expressions[program.loc+1].t) {
		case TOKEN:
			shouldbreak = 0;

			switch (program.expressions[program.loc+1].tktype) {
				case COLON: // definition
					define();
					shouldbreak = 1;
					break;
				case ARROW: break;
				case PLUS:
					if (program.expressions[program.loc+2].tktype == COLON) {
						program.loc += 3;
						int n = 0;

						const int loc_old = program.loc;

						if (find(program.thisScope.variables, program.expressions[program.loc-3].contents, &n)) {
							switch (program.thisScope.variables.at(n).type) {
								case INTEGER:
									program.thisScope.variables.at(n).val = std::to_string(std::stoi(program.thisScope.variables.at(n).val) + std::stoi(getval().val));
									break;
								case LIST:
									program.thisScope.variables.at(n).vals.push_back(getval());
									program.thisScope.variables.at(n).length = program.thisScope.variables.at(n).vals.size();
									break;
								case STRING:
									program.thisScope.variables.at(n).val += getval().val;
									break;
								case STS_BOOL: error(4, program.thisScope.variables.at(n).name);
							}
						}
						else error(8, program.expressions[program.loc-3].contents);
						
						program.loc = loc_old;
						shouldbreak = 1;
					}
					break;
				case DOT:
					objectMember();

					shouldbreak = true;

					break;
			}

			if (shouldbreak) break;
		case ENDEXPR:
			find(program.thisScope.functions, program.expressions[program.loc].contents, &fnum); // run isFunc to get function number
			runfunc(fnum);
			break;
		case UNKNOWN:
			declareObject();
			break;
	}
}

void interp(int psize, char *argv[], int argc) {
	parse();
	parseErrors();

	program.thisScope.variables.push_back(stsvars());
	for (int x = 1; x<=argc-1; x++) {
		program.thisScope.variables.back().type = LIST;
		program.thisScope.variables.back().vals.resize(program.thisScope.variables.back().vals.size()+1);
		program.thisScope.variables.back().vals.back().type = STRING;
		program.thisScope.variables.back().vals.back().val = argv[x];
		program.thisScope.variables.back().name = "arg";
		program.thisScope.variables.back().length = argc-1;
	}
	program.thisScope.types.push_back(socketClass());
	
	
	newScope();
}
