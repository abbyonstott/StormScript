#pragma once
#ifndef STSCLASSES_H_
#define STSCLASSES_H_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>
#include <cstdlib>

using std::string;
using std::cout;
using std::endl;

class sts
{
public:
	int lineon;
	unsigned int sizeoff = 0;
	std::vector<string> vars;
	void out(string str);
	string svar_name = ""; //name of string
	string ivar_name = ""; //name of integer
	string svar_cont = ""; //contents of string
	int ivar_cont; //contents of integer
	string sivar_cont; //contents of ivar as string
	int var_num = 0; //number of variables
	string line;
	void readline(string prg[], int big);
	void error(int num, string issue);
	void read(string filename);
};

#endif
