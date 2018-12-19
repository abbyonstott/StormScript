#pragma once
#ifndef STSCLASSES_H_
#define STSCLASSES_H_

#if defined(_WIN32)
#define PLATFORM "Windows"
#else
#define PLATFORM "other"
#endif

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>
#include <cstdlib>
#include "../StormScriptconfig.h"

using std::string;
using std::cout;

class sts;
class stsvars;
class stsfunc;

string striplit(string line);
bool condition(sts *program, int *ln, std::vector<stsvars> vars);
bool isint(string s);

class stsvars{
public:
	int valint = 0;
	int length;
	std::vector<stsvars> vals;
	string valstring = "";
	bool val, glob;
	string name;
	char type;

	void assignlist(sts *script, std::vector<stsvars> vars, int *line);
};

class stsclass {
public:
	void declare(int *y, sts *inst);
	void decmethod(sts *inst, int *ln);
	std::vector<stsvars> variables;
	std::vector<stsfunc> methods;
	string name;
};

class stsclasstype:public stsvars{
public:
	stsclass tpe;
	std::vector<int> indexes;
};

class stsfunc:public stsvars{
public:
	int linestarted; // line funcion code starts, not line "func" keyword is used
	bool classmethod = false;
	stsvars value;
	string cof;
	string modname = "main";
	stsclasstype cval;
	char valtype;
	std::vector<stsvars> args;
};


class sts
{
public:
	//variables
	int lineon; //line the parser is on
	unsigned int sizeoff = 0; //size of the program
	std::vector<stsfunc> functions; //functions
	std::vector<string> names; //imported libraries
	std::vector<string> prg; //unparsed program
	std::vector<string> prs; //parsed program
	std::vector<stsvars> globvars; //global variables
	std::vector<stsclass> classes;
	bool term;



	//functions
	stsvars getval(std::vector<stsvars> vars, int *line);
	stsvars declare(char type, int *line, std::vector<stsvars> *vars); //declare variables -
	void error(int num, string issue); //error
	void read(char *argv[], int argc, string filename); //read file
	void print(int line, int *y, std::vector<stsvars> current_vars); //out function
	void sys(int *y, std::vector<stsvars> vars);
	stsvars in(int line);
	std::vector<string> parse(std::vector<string> prg);
	void interp(string fname, int psize, char *argv[], int argc);
	void addmodule(int *ln);
	bool compare(int *y, std::vector<stsvars> current_vars);
	void ifs(int *line, int *endr, std::vector<stsvars> vars);
	void exec(int *x, int function, std::vector<stsclasstype> *pclasstypes, std::vector<stsvars*> objects);
	void runfunc(std::vector<stsvars> * pvars, std::vector<stsclasstype> *classtypes, int * ln);
	void set(string command, string setto, int x); // set command
	string runlibfunc(string name, int *line, std::vector<stsvars> vars); // run library function
	bool valchange(std::vector<stsvars> * pvars, std::vector<stsclasstype> *classtypes, int * ln);
	stsvars math(int *y, std::vector<stsvars> vars);
};



#endif