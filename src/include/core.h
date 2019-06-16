#pragma once
#ifndef CORE_H_
#define CORE_H_

#include "includes.h"
#include "variables.h"
#include "functions.h"
#include "parser.h"

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

	void runBuiltin(int *y, std::vector<stsvars> *scpvars, std::vector<stsfunc> *functions); // built in
	void runUnknown(int *y, std::vector<stsvars> *scpvars, std::vector<stsfunc> *functions); // user defined, declarations of variables, etc.

	//functions
	stsvars getval(std::vector<stsvars> *vars, std::vector<stsfunc> functions, int *line);

	void define(int *line, std::vector<stsvars> *vars, std::vector<stsfunc> functions); //declare variables

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

	string print(int *y, std::vector<stsvars> *current_var, std::vector<stsfunc> functions); // print function
	stsvars in(int *line);

	void sys(int *y, std::vector<stsvars> *vars, std::vector<stsfunc> functions) {
		*y += 1;

		system(getval(vars, functions, y).val.c_str());

		*y += 1;
	}

	void parseErrors();

	void newScope(int *y, std::vector<stsvars> *vars, std::vector<stsfunc> *functions);

	void parse(std::vector<string> prg);

	void interp(int psize, char *argv[], int argc);

	void ifs(std::vector<stsvars> *vars, std::vector<stsfunc> functions, int *y);

	void runfunc(int *y, std::vector<stsfunc> *functions, std::vector<stsvars> *variables, int num);

	stsvars readfile(int *y, std::vector<stsvars> *vars, std::vector<stsfunc> functions); // file reading operations; not to be confused with the language's reader, sts::read
	
	void writefile(int *y, std::vector<stsvars> *vars, std::vector<stsfunc> functions); // file writing operations

	void declareFunc(int *y, std::vector<stsfunc> *functions);

	void wait(std::vector<stsvars> *vars, std::vector<stsfunc> functions, int y) {
		#if PLATFORM == 1
			Sleep(std::stoi(getval(vars, functions, new int(y+1)).val) * 1000);
		#else
			sleep(std::stoi(getval(vars, functions, new int(y+1)).val));
		#endif
	}

	void importModules(int *y);
};
/*
Loop functions are defined here.
A vector of variables is returned so that modifications will be saved to actual values.
*/
void whileloop(sts *script, std::vector<stsvars> *variables, std::vector<stsfunc> functions, int *y);
void forloop(sts *script, std::vector<stsvars> *variables, std::vector<stsfunc> functions, int *y);

// this will iterate over y until it is the end of the while scope
void scopedown(int *x, std::vector<expression> expressions);

#endif
