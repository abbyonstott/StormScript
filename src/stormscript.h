#pragma once
#ifndef STORMSCRIPT_H_
#define STORMSCRIPT_H_

/*
* This macro changes executed code based on platform
* When platform is 1, it is on windows, otherwise run unix code
*/
#define PLATFORM (defined(_WIN32) || defined(__MINGW32__)) // true if on windows

#define VERSION "v1.1.0"

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <memory>
#include <stdio.h>
#include <unistd.h>

using std::cout;
using std::string;

// forward dec for use in program struct
class expression;
class type;
class stsfunc;
class stsvars;
class stsObject;

// basic scope info, so current variables, functions, objects, and types
struct scope {
	std::vector<type> types;
	std::vector<stsfunc> functions;
	std::vector<stsvars> variables;
	std::vector<stsObject> objects;

	scope(std::vector<stsfunc> f = {}, std::vector<stsvars> v = {}, std::vector<type> t = {}, std::vector<stsObject> V = {}) {
		types = t;
		functions = f;
		variables = v;
		objects = V;
	}
};

// this is the base struct with program info
inline struct program_t {
	int loc = 0;
	int function = -1;

	// looping flag is global to allow nested loops not all breaking on a break token not inside the original loop
	bool looping = false;
	
	string filename;

	std::vector<expression> expressions;

	/*
	* The reason that thisScope is initialized with the program_t struct is
	* because it is tied with the program. 
	*
	* When a new program_t instance is created, 
	* it should have a new scope to go with it
	*/
	scope thisScope; // this is the current scope, and it is initialized with the global scope
} program; // I will also declare the program struct type here and just use it with "backup" versions for function scopes

void error(int num, string issue);

enum ExprType {
	BUILTIN,
	UNKNOWN, // user defined things
	VALUE,
	TOKEN,
	ENDEXPR
};

enum tokenType { // tokens
	NOTOKEN,
	IS,
	NOT,
	LESS,
	LESSEQ,
	GREATER,
	GREATEREQ,
	TERNARY1,
	COLON,
	ARROW,
	OPENCURL,
	CLOSEDCURL,
	OPENBRACKET,
	CLOSEDBRACKET,
	PLUS,
	MINUS,
	DIVISION,
	MULTIPLICATION,
	COMMA,
	DOT
};

enum Builtin { // these are built in commands
	NONE,
	PRINT,
	PRINTL,
	STSIN,
	IF,
	ELSE,
	FUNCTION,
	TYPE,
	TYPE_INTEGER,
	TYPE_STRING,
	TYPE_STS_BOOL,
	TYPE_LIST,
	CONSTRUCTOR_SCOPE,
	MODULE,
	RETURN,
	WHILE,
	FOR,
	FOREACH,
	EXIT,
	SYSTEM,
	WAIT,
	WRITE,
	READ,
	RANDOM,
	RANDOMRANGE,
	LENGTH,
	BREAK,
	STSSOCKET
};

enum Value { // these are types
	INTEGER,
	STRING,
	STS_BOOL,
	LIST
};

class expression {
public:
	string contents;

	expression(string c = "") {
		contents = c;
	}

	ExprType t; // give type of expression
	tokenType tktype = NOTOKEN;
	Builtin btn = NONE;
	Value literalType;
	int line;
};

class stsvars {
public:
	Value type;
	string val;

	std::vector<stsvars> vals;

	int length;
	string name;

	void assignlist();
};

class stsfunc:public stsvars{
public:
	std::vector<expression> contents;
	std::vector<stsvars> args;

	program_t funcprog;
};

class type {
public:
	string name;

	std::vector<stsvars> members;
	std::vector<stsfunc> methods;
};

class stsObject: public type {
public:
	string Parentname;

	stsObject(const type &_Parent = type()) {
		Parentname = _Parent.name;
		members = _Parent.members;
		methods = _Parent.methods;
	}
};

stsvars getval();

// basic functions
string striplit(string line);
bool isint(string s);
bool toBool(string s);

// go down a scope
void scopedown();

// There might be a better place to put this
void importModules(int *i);

#endif // STORMSCRIPT_H_
