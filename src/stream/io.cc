#include "../stormscript.h"
#include "sts_stream.h"

string print() { //handles both print and printl.
	program.loc++;
	stsvars v = getval();
	string value = v.val;

	return value;
}

stsvars in() {
	stsvars input;

	input.name = program.expressions[program.loc+1].contents;

	char valstring[256]; // allocate a 256 bit char array for value storage

	std::cin.getline(valstring, 256); // use std::cin.getline to get value
	input.val = valstring;

	input.type = ((isint(input.val)) ? INTEGER : STRING);
	
	input.length = input.val.size();

	program.loc += 2;

	return input;
}