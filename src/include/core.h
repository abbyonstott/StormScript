#pragma once
#ifndef CORE_H_
#define CORE_H_

#include "includes.h"
#include "variables.h"
#include "functions.h"
#include "classes.h"

class sts
{
public:
	//variables
	int lineon; //line the parser is on
	unsigned int sizeoff = 0; //size of the program
	std::vector<stsfunc> functions; //functions
	std::vector<string> prg; //unparsed program
	std::vector<string> prs; //parsed program
	std::vector<stsvars> globvars; //global variables
	std::vector<stsclass> classes;
	bool term;



	//functions
	stsvars getval(std::vector<stsvars> vars, int *line);
	stsvars declare(int *line, std::vector<stsvars> *vars); //declare variables -

	void error(int num, string issue) {
		string cmd = "errors.sts ";
		cmd += std::to_string(num);
		cmd += " ";
		cmd += issue;
		system(cmd.c_str());

		if (term!=true)
			exit(1); // exit with error status
	}

	void read(char *argv[], int argc, string filename); //read file
	string print(int *y, std::vector<stsvars> current_vars); //out function
	void sys(int *y, std::vector<stsvars> vars);
	stsvars in(int line);
	std::vector<string> parse(std::vector<string> prg);
	void interp(string fname, int psize, char *argv[], int argc);
	bool compare(int *y, std::vector<stsvars> current_vars);
	void ifs(int *line, int *endr, std::vector<stsvars> vars);
	void exec(int *x, int function, std::vector<stsclasstype> *pclasstypes, std::vector<stsvars*> objects, std::vector<stsvars> *variables);
	void runfunc(std::vector<stsvars> * pvars, std::vector<stsclasstype> *classtypes, int * ln);
	void set(string command, string setto, int x); // set command
	string runlibfunc(string name, int *line, std::vector<stsvars> vars); // run library function
	bool valchange(std::vector<stsvars> * pvars, std::vector<stsclasstype> *classtypes, int * ln);
	stsvars math(int *y, std::vector<stsvars> vars);
	void readfile(int y, stsvars *v); // file reading operations
	void writefile(int y); // file writing operations
};

std::vector<stsvars> whileloop(sts *script, std::vector<stsvars> variables, int y);

#endif
