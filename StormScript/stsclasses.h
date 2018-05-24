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
	int lineon; //line the parser is on
	unsigned int sizeoff = 0; //size of the program
	std::vector<string> varnames; //variable names
	std::vector<string> vars; //variable contents
	//function
	void readline(string prg[], int psize); //read lines
	void error(int num, string issue); //error
	void read(string filename); //read file
	void out(string str); //out function
	void decvar(string contents, char type);
};

#endif
