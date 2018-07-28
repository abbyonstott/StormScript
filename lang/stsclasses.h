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

using std::string;
using std::cout;
using std::endl;

class sts
{
public:
	//variables
	int lineon; //line the parser is on
	unsigned int sizeoff = 0; //size of the program
	bool onloop=false;
	std::vector<string> varnames; //variable names
	std::vector<string> vars; //variable contents
	std::vector<string> prg;
	std::vector<string> prs;
	std::vector<string> functions;
	std::vector<string> fval;
	//functions
	string declare(char type, int line); //declare variables
	string bdeclare(char type, int line); //allows for declaration without values
	void error(int num, string issue); //error
	void read(string filename); //read file
	string out(int line); //out function
	string in(int line); //in function
	std::vector<string> parse(std::vector<string> prg);
	void decvar(string contents, char type); //declare variables
	void compile(string fname, std::vector<string> prg, int psize); //compiler
	int loop(string line);
	string fdeclare(int lifixne);
	int checkiffunction(string line);
};

#endif