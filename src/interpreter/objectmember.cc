#include "../include/stormscript.h"

void sts::objectMember(int *y) {
	/*
	* Find object 
	*/

	int ObjNum, MemberNum;

	// find object
	find(thisScope->objects, expressions[*y].contents, &ObjNum);

	if (expressions[*y+3].tktype == ARROW && thisScope->objects[ObjNum].Parentname == "socket") { // socket functions are handled by c++, not stormscript
		if (expressions[*y+2].contents == "await") {
			*y += 4;
			if (expressions[*y].t != VALUE && expressions[*y].t != UNKNOWN) 
				error(5, "await"); // generic "function requires args error"
			
			string msg = getval(y).val; // message to be sent to client

			*y += 2;
			bool output = toBool(getval(y).val); // determines whether to output connection or not

			thisScope->objects[ObjNum] = awaitSocket(thisScope->objects[ObjNum], msg, output);
		}
		else if (expressions[*y+2].contents == "connect") {
			*y += 4;
			if (expressions[*y].t != VALUE && expressions[*y].t == UNKNOWN)
				error(5, "connect");
			
			string msg = getval(y).val; // message to be sent to server

			thisScope->objects[ObjNum] = connectSocket(thisScope->objects[ObjNum], msg);
		}

		return;
	}
	
	*y += 2;

	// find member or method

	if (expressions[*y+1].tktype == COLON) {

		find(&thisScope->objects[ObjNum].members, expressions[*y].contents, &MemberNum);

		stsvars newval = getval(y);

		if (thisScope->objects[ObjNum].members[MemberNum].type == newval.type) 
			thisScope->objects[ObjNum].members[MemberNum].val = newval.val;
		else error(2, expressions[*y].contents);
	}
	else {
		find(thisScope->objects[ObjNum].methods, expressions[*y].contents, &MemberNum);

		sts typests;

		typests.expressions.push_back(expression());
		typests.expressions[0] = expressions[*y];

		*y += 1;

		if (expressions[*y].tktype == ARROW) {
			while (expressions[*y].t != ENDEXPR) {
				typests.expressions.push_back(expression());
				typests.expressions.back() = expressions[*y];

				*y += 1;
			}
		}

		typests.expressions.push_back(expression());
		typests.expressions.back() = expressions[*y];
		
		typests.thisScope->functions.push_back(thisScope->objects[ObjNum].methods[MemberNum]);
		typests.thisScope->variables.insert(typests.thisScope->variables.begin(), thisScope->objects[ObjNum].members.begin(), thisScope->objects[ObjNum].members.end());

		typests.runfunc(new int(0), 0);

		thisScope->objects[ObjNum].members = typests.thisScope->variables;
	}

	return;
}