#include "stormscript.h"

bool toBool(string s) {
	return (s == "true");
}

string striplit(string line) {
	line.pop_back();
	line.erase(line.begin());

	return line;
}

bool isint(string s) {
	for (int i = 0; i < s.size(); i++) {
		if ((std::isdigit(s[i])) || ((s[i]=='-') && (std::isdigit(s[i]))))
			return true;
		else
			return false;
	}

	return false;
}

void scopedown() { // exit current scope
	int endreq = 1;

	while (endreq != 0)  {
		if (program.expressions[program.loc].tktype == OPENCURL) endreq += 1;
		else if (program.expressions[program.loc].tktype == CLOSEDCURL) endreq -= 1;

		program.loc++;
	}
	program.loc--;
}
