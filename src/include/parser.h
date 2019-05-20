#pragma once
#ifndef PARSER_H_
#define PARSER_H_

#include "includes.h"
#include "core.h"

// enumerations and expression class

enum ExprType {
	BUILTIN,
	UNKNOWN, // user defined things
	TOKEN,
	ENDEXPR
};

enum TokenType { // tokens
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
	MULTIPLICATION
};

enum Builtin { // these are built in commands
    PRINT,
    PRINTL,
    IN,
    IF,
    ELSE,
    SET,
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
    READ
};

class expression {
public:
	string contents;

	expression(string c) {
		contents = c;
	}

	ExprType t; // give type of expression
	TokenType tktype;
    Builtin btn;
};

#endif