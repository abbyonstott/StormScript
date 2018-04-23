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
	bool fin = false; //finished
	string timesstr; //times to run as string
	int times; //times to run as int
	int lineon; //line the parser is on
	unsigned int sizeoff = 0; //size of the program
	std::vector<string> vars; //variables
	string svar_name = ""; //name of string
	string ivar_name = ""; //name of integer
	string svar_cont = ""; //contents of string
	int ivar_cont; //contents of integer
	string sivar_cont; //contents of ivar as string
	int var_num = 0; //number of variables
	//function
	bool readline(string prg[], int big); //read lines
	void error(int num, string issue); //error
	void read(string filename); //read file
	void out(string str); //out function
};

#endif
