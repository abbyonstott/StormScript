#include "../include/stormscript.h"

void sts::error(int num, string issue)
{
	if (num == 0) {
		cout << "Error: No input files.\nTry 'stormscript --help' for more information.\n";
	}
	else if (num == 1) {
		cout << "Error: \"" << issue << "\" is not a recognised command\n";
	}
	else if (num == 2) {
		cout << "Error: \"" << issue << "\" is not a recognised type\n";
	}
	else if (num == 3) {
		cout << "Error: \"" << issue << "\" is not a valid expression\n";
	}
	else if (num == 4) {
		cout << "Error: \"" << issue << "\" is an unsupported type\n";
	}
	else if (num == 5) {
		cout << "Error: \"" << issue << "\" is an array and must use a subscript on print\n";
	}
	else if (num == 6) {
		cout << "Error: \"" << issue << "\" is out of range\n"; 
	}
	else if (num == 7) {
		cout << "Error: return is not allowed in do{ function.\n";
	}
	else if (num == 8) {
		cout << "Error: \"" << issue << "\" is not a value.\n";
	}
	else if (num == 9) {
		cout << "Error: \"" << issue << "\" is not the correct type.\n";
	}
	else if (num == 10) {
		cout << "Error: variable used in 'sys' command is of type " << issue << " and should be a str.\n";
	}
	else if (num == 11) {
		cout << "Error: failed to open \"" << issue << "\". Couldn't find file.\n"; 
	}
	else if (num == 12) {
		cout << "Error: Variable \"" << issue << "\" not found.\n";
	}
	else if (num == 13) {
		cout << "Error: Expected library name\n";
	}
	else if (num == 14) {
		cout << "Error: Missing end quote on literal\"" << issue << "\".\n";
	}
	if (term!=true) {
		exit(0);
	}
}
