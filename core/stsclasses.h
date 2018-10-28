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
using std::endl;


class stsvars{
public:
	int valint = 0;
	std::vector<int> valsint;
	string valstring = "";
	std::vector<string> valsstring;
	bool val;
	char type;
	bool glob;
	string name;
};

class stsfunc:public stsvars{
public:
	int linestarted;
	stsvars value;
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
	//functions
	stsvars declare(char type, int line); //declare variables -
	void error(int num, string issue); //error
	void read(char *argv[], int argc); //read file
	void print(int line, std::vector<stsvars> current_vars); //out function
	void sys(int line,std::vector<stsvars> vars);
	stsvars in(int line);
	std::vector<string> parse(std::vector<string> prg);
	void interp(string fname, std::vector<string> prg, int psize, char *argv[], int argc);
	bool compare(int line, std::vector<stsvars> current_vars);
	void exec(int line, std::vector<string> names, int function);
	void valchange(std::vector<stsvars> * pvars, int * ln);
};



#endif
