#pragma once
#ifndef CORE_H_
#define CORE_H_

#include "includes.h"
#include "variables.h"
#include "functions.h"
#include "classes.h"
#include "parser.h"

class sts
{
public:
	//variables
	int lineon; //line the parser is on
	int function = -1;
	unsigned int sizeoff = 0; //size of the program
	std::vector<string> prg; //unparsed program
	std::vector<string> prs; //parsed program. FINALLY WILL BE REMOVED!!!!!111!!!!1!!!
	std::vector<stsvars> globvars; //global variables
	std::vector<stsclass> classes;
	std::vector<expression> expressions; // Replacing prs. Same thing with more info
	bool term;

	void runBuiltin(int *y, std::vector<stsvars> *scpvars, std::vector<stsfunc> *functions); // built in
	void runUnknown(int *y, std::vector<stsvars> *scpvars, std::vector<stsfunc> *functions); // user defined, declarations of variables, etc.

	//functions
	stsvars getval(std::vector<stsvars> vars, std::vector<stsfunc> functions, int *line);

	void define(int *line, std::vector<stsvars> *vars, std::vector<stsfunc> functions); //declare variables

	void error(int num, string issue) {
		string cmd = "errors.sts ";
		cmd += std::to_string(num);
		cmd += " ";
		cmd += issue;
		system(cmd.c_str());

		if (term!=true)
			exit(1); // exit with error status
	}

	void live(string filename) {
		string cmd = "live.sts ";
		cmd += filename;
		system(cmd.c_str());
	}

	void evaluateProgram();

	void read(char *argv[], int argc, string filename); // read stormscript programs

	string print(int *y, std::vector<stsvars> current_var, std::vector<stsfunc> functions); // print function
	stsvars in(int line);

	void sys(int *y, std::vector<stsvars> vars);

	void newScope(int *y, std::vector<stsvars> vars, std::vector<stsfunc> *functions);

	void parse(std::vector<string> prg);

	void interp(string fname, int psize, char *argv[], int argc);

	void ifs(std::vector<stsvars> vars, std::vector<stsfunc> functions, int *y);

	void runfunc(int *y, std::vector<stsfunc> *functions, int num);

	void set(int *y);

	bool valchange(std::vector<stsvars> * pvars, std::vector<stsclasstype> *classtypes, int * ln);

	void readfile(int y, stsvars *v, std::vector<stsvars> vars); // file reading operations; not to be confused with the language's reader, sts::read
	
	void writefile(int y, std::vector<stsvars> vars); // file writing operations

	void declareFunc(int *y, std::vector<stsfunc> *functions);
};


/*
Loop functions are defined here.
A vector of variables is returned so that modifications will be saved to actual values.
*/
std::vector<stsvars> whileloop(sts *script, std::vector<stsvars> variables, int y);
std::vector<stsvars> forloop(sts *script, std::vector<stsvars> variables, int y);
std::vector<stsvars> foreach(sts *script, std::vector<stsvars>, int y);

// this will iterate over y until it is the end of the while scope
void scopedown(int *x, std::vector<expression> expressions);

#endif
