#pragma once
#ifndef CORE_H_
#define CORE_H_

#include "includes.h"
#include "variables.h"
#include "functions.h"
#include "parser.h"
#include "type.h"
#include "scope.h"

class sts
{
public:
	//variables
	int lineon; //line the parser is on
	string filename; // filename
	int function = -1;
	/*
	 * What the function numbers mean:
	 * -1: Not a function
	 * -2: A loop
	 * > 1: The number of the function that is running
	*/
	bool looping = false;
	unsigned int sizeoff = 0; //size of the program
	std::vector<string> prg; //unparsed program
	std::vector<expression> expressions;

	scope *thisScope = new scope(); // this is the current scope, and it is initialized with the global scope

	void runBuiltin(int *y); // built in
	void runUnknown(int *y); // user defined, declarations of variables, etc.

	//functions
	stsvars getval(int *line);

	void define(int *line); //declare variables

	void error(int num, string issue) { 
		// in order for errors to work stormscript has to be in PATH, but we can assume that it is installed to usr/bin
		string cmd;

		#if (PLATFORM == 1)
		cmd = "stormscript errors.sts ";
		#else
		cmd = "stormscript /usr/share/stormscript/errors.sts ";
		#endif
		
		cmd += std::to_string(num);
		cmd += " ";
		cmd += issue;
		system(cmd.c_str());
		exit(0);
	}

	void evaluateProgram();

	void read(char *argv[], int argc); // read stormscript programs

	string print(int *y); // print function
	stsvars in(int *line);

	void sys(int *y) {
		*y += 1;

		system(getval(y).val.c_str());

		*y += 1;
	}

	void parseErrors();

	void newScope(int *y);

	void parse(std::vector<string> prg);

	void interp(int psize, char *argv[], int argc);

	void ifs(int *y);

	void runfunc(int *y, int num);

	stsvars readfile(int *y); // file reading operations; not to be confused with the language's reader, sts::read
	
	void writefile(int *y); // file writing operations

	void declareFunc(int *y);

	void declareType(int *y);

	void wait(int y) {
		#if PLATFORM == 1
			Sleep(std::stoi(getval(new int(y+1)).val) * 1000);
		#else
			sleep(std::stoi(getval(new int(y+1)).val));
		#endif
	}

	void importModules(int *y);
};
/*
Loop functions are defined here.
*/
void whileloop(sts *script, scope *current, int *y);
void forloop(sts *script, scope *current, int *y);

// this will iterate over y until it is the end of the while scope
void scopedown(int *x, std::vector<expression> expressions);

#endif
