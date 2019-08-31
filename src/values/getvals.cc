#include "../stormscript.h"
#include "../stream/sts_stream.h"
#include "sts_values.h"

void replaceEscapes(string *lit) { // escapes
	string newl;

	for (int i = 0; i < lit->size(); i++) {
		if (lit->at(i) == '\\') {
			i++;
			
			switch (lit->at(i)) {
				case 'n':
					newl += '\n';
					break;
				case 't':
					newl += '\t';
					break;
				case '\\':
					newl += '\\';
					break;
				case '$':
					newl += '$';
					break;
			}
		}
		else if (lit->at(i) == '$') { // dollar sign for concatenation
			string q;

			i++;

			while (lit->at(i) != ' ') {
				q += lit->at(i);


				if (i == lit->size() - 1 ) break;
				else i++;
			}
			
			int loc;
			find(program.thisScope.variables, q, &loc);

			newl += program.thisScope.variables[loc].val;
			if (lit->at(i) == ' ') newl += ' ';
		}
		else {
			newl += lit->at(i);
		}
	}

	*lit = newl;
}

stsvars getval() {
	/*
	* THIS FILE IS VERY IMPORTANT!!!!!
	* When Modifying this function be sure that:
	*	a. The code works in every circumstance where a value would be needed (act as though any value is grabbed with one expression; add to program.loc until it reaches the end of the expression)
	*	b. The code uses returns a value with a type. Under no circumstance should the variable "v" have an empty type.
	*	c. This should go without saying, but please document your code. I don't want to remove anything important because I can't figure out what it does
	*/

	stsvars v;
	bool dotCompare = false; // dot operations take up 2 extra expression slots

	if (program.expressions[program.loc+1].tktype == DOT && program.expressions[program.loc+3].tktype != COMMA && program.expressions[program.loc+3].t != ENDEXPR
		&& program.expressions.size() > program.loc+3) {
		dotCompare = true;
		program.loc += 2;
	}

	bool operation = ((program.expressions[program.loc+1].t == TOKEN) && 
		(program.expressions[program.loc+1].tktype != COMMA) && (program.expressions[program.loc+1].tktype != COLON) && (program.expressions[program.loc+1].tktype != OPENCURL)  && (program.expressions[program.loc+1].tktype != CLOSEDBRACKET) && 
		(program.expressions[program.loc+1].tktype != DOT) &&
		(program.expressions.size() > program.loc+1));

	switch (operation) {
		case 0: // if raw value
			if (program.expressions[program.loc].t == VALUE) { // returns literals with proper types
				string lit;

				switch (program.expressions[program.loc].literalType) {
					case STRING:
						lit = striplit(program.expressions[program.loc].contents);
						v.type = 's';
						v.length = lit.size();
						replaceEscapes(&lit);
						break;
					case INTEGER:
					case STS_BOOL:
						v.type = ((program.expressions[program.loc].literalType == INTEGER) ? 'i' : 'b');
						lit = program.expressions[program.loc].contents;
						break;
				}

				v.val = lit;
			}
			else if (program.expressions[program.loc].t == BUILTIN) { 
				// stsread just reads the file, but it is always used as a value because it returns a value
				switch (program.expressions[program.loc].btn) { 
					case READ:
						v = readfile();
						break;
					case RANDOM:
						v.val = ((randombool()) ? "true" : "false");
						v.type = 'b';
						break;
					case RANDOMRANGE:
						v.val = std::to_string(genrandomintfromrange());
						v.type = 'i';
				}
			}
			else if (program.expressions[program.loc].t == UNKNOWN) {
				int index;

				if (find(program.thisScope.variables, program.expressions[program.loc].contents, &index) || find(program.thisScope.objects, program.expressions[program.loc].contents, &index)) {                    
					if (program.expressions[program.loc+1].tktype != DOT) v = program.thisScope.variables.at(index); // get value
					else if (program.expressions[program.loc+2].btn == LENGTH) { // get length
						program.loc+= 3;

						v.type = 'i';

						if ((program.thisScope.variables.at(index).type == 's') || (program.thisScope.variables.at(index).type == 'l'))
							v.val = std::to_string(program.thisScope.variables.at(index).length);

						else error(2, program.thisScope.variables.at(index).name);
					}
					else { // look for class members
						int MemberLoc;
						program.loc += 2;

						find(program.thisScope.objects[index].members, program.expressions[program.loc].contents, &MemberLoc);
						v = program.thisScope.objects[index].members[MemberLoc]; // return member
						
						program.loc++;
					}
				}
				else if (find(program.thisScope.functions, program.expressions[program.loc].contents, &index)) {
					runfunc(index);
					v = program.thisScope.functions[index]; // if expression refers to function
				}
			}

			break;
		case 1: // if operation
			tokenType t = program.expressions[program.loc+1].tktype;
			std::vector<program_t> placeholders;
			int index;
			stsvars sbsvar;
			tokenType plus1;

			int first, second;

			if ((t == PLUS) || (t == MINUS) || (t == DIVISION) || (t == MULTIPLICATION)) { 
				// all math operations will return an integer, so we can set that first
				v.type = 'i';

				placeholders.resize(2);

				placeholders.at(0).expressions = {program.expressions[program.loc]};
				placeholders.at(0).thisScope = program.thisScope;
				placeholders.at(1).expressions = {program.expressions[program.loc+2]};
				placeholders.at(1).thisScope = program.thisScope;

				program.loc+= 2;

				// for math, access placeholder values and store as first and second for operation
				program_t program_old = program;
				program = placeholders[0];
				first = std::stoi(getval().val);

				program = placeholders[1];
				second = std::stoi(getval().val);
				program = program_old;
			}
			else if (t == OPENBRACKET) {
				program.loc += 2;
				int er = 1;
				int i = program.loc;

				placeholders.resize(1);
				placeholders.back().thisScope = program.thisScope;

				while (er != 0) {
					if ((program.expressions[i].t == TOKEN) && (program.expressions[i].tktype == CLOSEDBRACKET))
						er--;
					else if ((program.expressions[i].t == TOKEN) && (program.expressions[i].tktype == OPENBRACKET))
						er++;

					if (er != 0)
						placeholders.back().expressions.push_back(program.expressions[i]);
					
					i++;
				}
				program_t program_old = program;
				program = placeholders[0];

				index = std::stoi(getval().val);

				program = program_old;
				
				int plus1n = placeholders[0].expressions.size() + program.loc + 1;  // loc of plus 1
				plus1 = ((plus1n >= program.expressions.size()) ? NOTOKEN : program.expressions[plus1n].tktype); // set to zero if last expression
			}

			switch (t) { // perform based on token type
				case PLUS: // I'm sure there is an easier way to do this...
					v.val = std::to_string(first + second);
					break;
				case MINUS:
					v.val = std::to_string(first - second);
					break;
				case DIVISION:
					v.val = std::to_string(first / second);
					break;
				case MULTIPLICATION:
					v.val = std::to_string(first * second);
					break; 
				case OPENBRACKET:
					if ((plus1 != IS) && (plus1 != NOT) && (plus1 != GREATER) && (plus1 != GREATEREQ) && (plus1 != LESS) && (plus1 != LESSEQ)) {
						int varn;
						find(program.thisScope.variables, program.expressions[program.loc-2].contents, &varn);

						sbsvar = program.thisScope.variables[varn];

						switch(sbsvar.type) {
							case 's':
								if ((index >= sbsvar.val.size()) || (index < 0)) {
									string fullexpr = sbsvar.name + "[";

									for (int n = 0; n < placeholders[0].expressions.size(); n++) // add full subscript to error details
										fullexpr += placeholders[0].expressions[n].contents;

									fullexpr += "]"; // add brackets for complete statement

									error(4, fullexpr);
								}

								v.type = 's';
								v.val = sbsvar.val[index];

								break;

							case 'l':
								if ((index >= sbsvar.vals.size()) || (index < 0)) { // out of range error
									string fullexpr = sbsvar.name + "[";

									for (int n = 0; n < placeholders[0].expressions.size(); n++) // add full subscript to error details
										fullexpr += placeholders[0].expressions[n].contents;

									fullexpr += "]"; // add brackets for complete statement

									error(4, fullexpr);
								}

								v = sbsvar.vals[index];

								break;

							case 'i': // subscripts don't work on int or bool, so give error
							case 'b':
								error(2, sbsvar.name);
								break;
						}
						program.loc += placeholders[0].expressions.size();

						break;
					}
					else
						program.loc -= 2;
				case IS:
				case NOT:
				case GREATER:
				case GREATEREQ:
				case LESS:
				case LESSEQ:
					// subtract 2 for condition function to get values
					if (dotCompare) program.loc -= 2;
					v.val = ((condition()) ? "true" : "false");

					if (program.expressions[program.loc].tktype == TERNARY1) {
						/* 
						For ternary, we can assume that it is structured like this:
							 TOKEN   | VALUE/UNKNOWN |   TOKEN   | VALUE/UNKNOWN
						-----------|---------------------------|--------------
							?      |     var       |     :     |     var

						as usual, these values can be anything, but getval() automatically fills in the gap so we don't have to do much here with different cases
						*/
						int _loc = program.loc;
						bool _val = toBool(v.val);
						stsvars primary, secondary;

						program.loc++;
						primary = getval();
						program.loc = _loc;

						while (program.expressions[program.loc].tktype != COLON) program.loc++; 
						program.loc += 2;
						secondary = getval();
						program.loc = _loc;

						v.val = ((_val) ? primary.val : secondary.val);
						v.type = ((_val) ? primary.type : secondary.type);
						
						// exit ternary:
						while (program.expressions[++program.loc].t != ENDEXPR);
					}
					break;
			}

			break;
	}
	return v;
}