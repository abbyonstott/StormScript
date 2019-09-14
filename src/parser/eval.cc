#include "../stormscript.h"
#include "sts_parser.h"

Value getValue(string ctn) {
	if (ctn.front() == '\"') return STRING;
	else if (isint(ctn)) return INTEGER;
	else if ((ctn == "true") || (ctn == "false")) return STS_BOOL;
	return NOVAL;
}

tokenType gettktype(string tkn) {
	if (tkn == "is") return IS;
	else if (tkn == "not") return NOT;
	else if (tkn == "less") return LESS;
	else if (tkn == "lesseq") return LESSEQ;
	else if (tkn == "greater") return GREATER;
	else if (tkn == "greatereq") return GREATEREQ;
	else if (tkn == "?") return TERNARY1;
	else if (tkn == ":") return COLON;
	else if (tkn == "=>") return ARROW;
	else if (tkn == "{") return OPENCURL;
	else if (tkn == "}") return CLOSEDCURL;
	else if (tkn == "[") return OPENBRACKET;
	else if (tkn == "]") return CLOSEDBRACKET;
	else if (tkn == "+") return PLUS;
	else if (tkn == "-") return MINUS;
	else if (tkn == "/") return DIVISION;
	else if (tkn == "*") return MULTIPLICATION;
	else if (tkn == ",") return COMMA;
	else if (tkn == ".") return DOT;
	return NOTOKEN;
}

Builtin getBuiltincmd(string kwd) {
	if (kwd == "print") return PRINT;
	else if (kwd == "printl") return PRINTL;
	else if (kwd == "in") return STSIN;
	else if (kwd == "if") return IF;
	else if (kwd == "else") return ELSE;
	else if (kwd == "func") return FUNCTION;
	else if (kwd == "type") return TYPE;
	else if (kwd == "int") return TYPE_INTEGER;
	else if (kwd == "str") return TYPE_STRING;
	else if (kwd == "bool") return TYPE_STS_BOOL;
	else if (kwd == "list") return TYPE_LIST;
	else if (kwd == "init") return CONSTRUCTOR_SCOPE;
	else if (kwd == "mod") return MODULE;
	else if (kwd == "return") return RETURN;
	else if (kwd == "while") return WHILE;
	else if (kwd == "for") return FOR;
	else if (kwd == "foreach") return FOREACH;
	else if (kwd == "exit") return EXIT;
	else if (kwd == "sys") return SYSTEM;
	else if (kwd == "wait") return WAIT;
	else if (kwd == "write") return WRITE;
	else if (kwd == "read") return READ;
	else if (kwd == "random") return RANDOM;
	else if (kwd == "randomrange") return RANDOMRANGE;
	else if (kwd == "length") return LENGTH;
	else if (kwd == "break") return BREAK;
	else if (kwd == "socket") return STSSOCKET;
	else if (kwd == "private") return TYPE_PRIVATE;
	return NONE;
}

void evaluateProgram() {
	for (int i = 0; i < program.expressions.size(); i++) {
		string contents = program.expressions[i].contents;
		Builtin btn = getBuiltincmd(contents);
		tokenType tktype = gettktype(contents);
		Value val = getValue(contents);

		if (btn != NONE) {
			program.expressions[i].t = BUILTIN;
			program.expressions[i].btn = btn;
		}
		else if (gettktype(contents) != NOTOKEN) {
			program.expressions[i].t = TOKEN;
			program.expressions[i].tktype = tktype;
		}
		else if (val != NOVAL) {
			program.expressions[i].t = VALUE;
			program.expressions[i].literalType = val;
		}
		else if (contents == ";")
			program.expressions[i].t = ENDEXPR;
		else
			program.expressions[i].t = UNKNOWN;

	}
}
