#include "../stormscript.h"
#include "sts_type.h"
#include "../networking/networking.h"

void objectMember() {
	/*
	* Find and manipulate object members
	* run class methods
	*/

	int ObjNum, MemberNum;

	// find object
	find(program.thisScope.objects, program.expressions[program.loc].contents, &ObjNum);

	if (program.expressions[program.loc+3].tktype == ARROW && program.thisScope.objects[ObjNum].Parentname == "socket") { // socket functions are handled by c++, not stormscript
		if (program.expressions[program.loc+2].contents == "await") {
			program.loc += 4;

			if (program.expressions[program.loc].t != VALUE && program.expressions[program.loc].t != UNKNOWN) 
				error(5, "await"); // generic "function requires args error"
			
			string msg = getval().val; // message to be sent to client

			program.loc += 2;
			bool output = toBool(getval().val); // determines whether to output connection or not

			program.thisScope.objects[ObjNum] = awaitSocket(program.thisScope.objects[ObjNum], msg, output);
		}
		else if (program.expressions[program.loc+2].contents == "connect") {
			program.loc += 4;
			if (program.expressions[program.loc].t != VALUE && program.expressions[program.loc].t == UNKNOWN)
				error(5, "connect");
			
			string msg = getval().val; // message to be sent to server

			program.thisScope.objects[ObjNum] = connectSocket(program.thisScope.objects[ObjNum], msg);
		}

		return;
	}
	
	program.loc += 2;

	// find member or method

	if (program.expressions[program.loc+1].tktype == COLON) {
		// definition

		find(program.thisScope.objects[ObjNum].members, program.expressions[program.loc].contents, &MemberNum);

		program.loc += 2;

		stsvars newval = getval();

		if (program.thisScope.objects[ObjNum].members[MemberNum].type == newval.type) 
			program.thisScope.objects[ObjNum].members[MemberNum].val = newval.val;
		else error(2, program.expressions[program.loc].contents);
	}
	else {
		find(program.thisScope.objects[ObjNum].methods, program.expressions[program.loc].contents, &MemberNum);

		program_t program_old = program;

		/*
		 * Class methods are run in there own mini
		 * programs to isolate the class members
		*/
		program.loc = 0;
		program.expressions.clear();
		program.expressions.push_back(expression());
		program.expressions[0] = program_old.expressions[program_old.loc];

		program_old.loc += 1;

		if (program_old.expressions[program_old.loc].tktype == ARROW) {
			while (program_old.expressions[program_old.loc].t != ENDEXPR) {
				program.expressions.push_back(program_old.expressions[program_old.loc]);

				program_old.loc += 1;
			}
		}

		program.expressions.push_back(program_old.expressions[program_old.loc]);
		
		program.thisScope.functions.push_back(program.thisScope.objects[ObjNum].methods[MemberNum]);
		program.thisScope.variables.insert(program.thisScope.variables.begin(), program.thisScope.objects[ObjNum].members.begin(), program.thisScope.objects[ObjNum].members.end());

		runfunc(0);

		program_old.thisScope.objects[ObjNum].members = program.thisScope.variables;

		program = program_old;
	}
}