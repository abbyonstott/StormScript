#include "../stormscript.h"

#include "../values/sts_values.h"
#include "../networking/networking.h"
// for declare object to call evaluate program
#include "../parser/sts_parser.h"

void declareType() {
	program.loc += 1;

	type t;

	t.name = program.expressions[program.loc].contents;
	
	program.loc += 2;

	while (program.expressions[program.loc].tktype != CLOSEDCURL) {
		stsvars obj;
		stsfunc c;

		switch (program.expressions[program.loc].btn) {
			case TYPE_INTEGER:
			case TYPE_STRING:
			case TYPE_LIST:
			case TYPE_STS_BOOL:
				if (program.expressions[program.loc].btn == TYPE_STS_BOOL) obj.type = 'b';
				else if (program.expressions[program.loc].btn == TYPE_INTEGER) obj.type = 'i';
				else if (program.expressions[program.loc].btn == TYPE_STRING) obj.type = 's';
				else obj.type = 'l';
				
				obj.name = program.expressions[++(program.loc)].contents;
				program.loc += 1;

				t.members.push_back(obj);
				break;
			case CONSTRUCTOR_SCOPE:
			case FUNCTION:
				program.loc += 1;

				if (program.expressions[program.loc -1].btn == FUNCTION) c.name = program.expressions[(program.loc)++].contents;
				else c.name = "init";

				if (program.expressions[program.loc].tktype == ARROW) {
					program.loc += 1;

					while (true) {

						if (program.expressions[program.loc].tktype == OPENCURL) break;
						else if (program.expressions[program.loc].tktype != COMMA) {
							c.args.push_back(stsvars());
							c.args.back().name = program.expressions[program.loc].contents;
						}
						program.loc += 1;
					}
				}

				program.loc += 1;

				int endreq = 1;

				while (endreq != 0) {
					if (program.expressions[program.loc].tktype == CLOSEDCURL) endreq--;
					else if (program.expressions[program.loc].tktype == OPENCURL) endreq++;

					c.contents.push_back(program.expressions[program.loc]);

					program.loc += 1;
				}
				program.loc -= 1; // subtract 1 because the previous scope automatically adds 1 at the end

				t.methods.push_back(c);
				break;
		}
		program.loc += 1;
	}

	program.thisScope.types.push_back(t);
}

void declareObject() {
	int num;
	int initnum;
	
	find(program.thisScope.types, program.expressions[program.loc].contents, &num);
	bool init = find(program.thisScope.types[num].methods, "init", &initnum); // find the init method

	stsObject t = program.thisScope.types[num];

	t.name = program.expressions[++(program.loc)].contents;

	if (program.thisScope.types[num].name == "socket") {
		// socket works as class
		program.loc += 2;

		string familyval = getval().val, address;

		program.loc += 2;
		address = getval().val;

		program.loc += 2;
		t = createSocket(familyval, address, std::stoi(getval().val), t);
		program.loc += 1;
	}
	else if (t.methods.size() > 0 && init) {
		program_t program_old = program;

		program.thisScope.functions.push_back(t.methods[initnum]);
		program.thisScope.variables.insert(program.thisScope.variables.begin(), t.members.begin(), t.members.end());

		program.expressions.push_back(expression());
		program.expressions[0].contents = "init";
		program.expressions[0].line = 1;
		// if there are arguments
		if (program_old.expressions[program_old.loc + 1].tktype == ARROW && program_old.thisScope.types[num].methods[initnum].args.size() > 0) {
			program_old.loc += 1;
			
			while (program_old.expressions[program_old.loc].t != ENDEXPR) {
				program.expressions.push_back(expression());
				program.expressions.back().contents = program.expressions[program.loc].contents;
				program.expressions.back().line = 1;

				program_old.loc += 1;
			}
		}
		else if (program_old.expressions[program_old.loc + 1].tktype == ARROW) // if user gives arguments when there are none
			error(10, t.Parentname);

		program.expressions.push_back(expression());
		program.expressions.back().line = 1;
		program.expressions.back().contents = ";";

		evaluateProgram();
		runfunc(0);

		t.members = program.thisScope.variables;
		program = program_old;
	}

	program.thisScope.objects.push_back(t);
}