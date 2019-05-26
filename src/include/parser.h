#pragma once
#ifndef PARSER_H_
#define PARSER_H_

#include "includes.h"
#include "core.h"

// enumerations and expression class

enum ExprType {
	BUILTIN,
	UNKNOWN, // user defined things
	VALUE,
	TOKEN,
	ENDEXPR
};

enum TokenType { // tokens
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
	COMMA
};

enum Builtin { // these are built in commands
	NONE,
    PRINT,
    PRINTL,
    IN,
    IF,
    ELSE,
    FUNCTION,
    TYPE,
    TYPE_INTEGER,
    TYPE_STRING,
    TYPE_BOOL,
    TYPE_LIST,
    TYPE_CONSTRUCTOR,
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
	RANDOMRANGE
};

enum Value { // these are types
	INTEGER,
	STRING,
	BOOLEAN
};

class expression {
public:
	string contents;

	expression(string c) {
		contents = c;
	}

	ExprType t; // give type of expression
	TokenType tktype = NOTOKEN;
    Builtin btn = NONE;
	Value literalType;
};

#endif