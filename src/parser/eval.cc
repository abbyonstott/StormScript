#include "../include/stormscript.h"

bool evaluateToken(string tkn) { // tokens are different types of operators and symbols
    if ((tkn == "is") || (tkn == "not") || (tkn == "less") || (tkn == "lesseq") || (tkn == "greater") || (tkn == "greatereq")) return 1; // comparison operators
    else if ((tkn == "?") || (tkn == ":") || (tkn == "=>") || (tkn == "{") || (tkn == "}") || (tkn == "[") || (tkn == "]")) return 1; // symbols
    else if ((tkn == "+") || (tkn == "-") || (tkn == "/") || (tkn == "*") || (tkn == ",") || (tkn == ".")) return 1;
    
    return 0;
}

bool evaluateBuiltin(string kwd) {
    if ((kwd == "int") || (kwd == "str") || (kwd == "bool") || (kwd == "init") ||(kwd == "list") || (kwd == "func") || (kwd == "type") || (kwd == "mod") || (kwd == "return")) return 1;
    else if ((kwd == "print") || (kwd == "printl") || (kwd == "in") || (kwd == "write") || (kwd == "read") || (kwd == "sys") || (kwd == "wait")) return 1;
    else if ((kwd == "if") || (kwd == "else") || (kwd == "exit") || (kwd =="for") || (kwd == "foreach") || (kwd == "while")) return 1;
    else if ((kwd == "random") || (kwd == "randomrange") || (kwd == "length") || (kwd == "break")) return 1;
    return 0;
}

bool evalLiteral(string ctn) {
    if ((ctn.front() == '\"') || (isint(ctn)) || (ctn == "true") || (ctn == "false")) return 1;

    return 0;
}
ExprType determinetype(string contents) {
    if (evaluateToken(contents)) return TOKEN;
    else if (evaluateBuiltin(contents)) return BUILTIN;
    else if (evalLiteral(contents)) return VALUE;
    else if (contents == ";") return ENDEXPR;

    return UNKNOWN;
}

Value getValue(string ctn) {
    if (ctn.front() == '\"') return STRING;
    else if (isint(ctn)) return INTEGER;
    else if ((ctn == "true") || (ctn == "false")) return STS_BOOL;
    return LIST;
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
    return NONE;
}

void sts::evaluateProgram() {
    for (int i = 0; i < expressions.size(); i++) {
        expressions[i].t = determinetype(expressions[i].contents);

        if (expressions[i].t == TOKEN)
            expressions[i].tktype = gettktype(expressions[i].contents);
        else if (expressions[i].t == BUILTIN)
            expressions[i].btn = getBuiltincmd(expressions[i].contents);
        else if (expressions[i].t == VALUE)
            expressions[i].literalType = getValue(expressions[i].contents);
    }

    parseErrors();
}
