#include "stsclasses.h"

void sts::error(int num, string issue)
{
	if (num == 0)
	{
		cout << "Error: No input files" << endl;
	}
	else if (num == 1)
	{
		cout << "Error: \"" << issue << "\" is not a recognised command" << endl;
	}
	else if (num == 2)
	{
		cout << "Error: \"" << issue << "\" is not a recognised type" << endl;
	}
	else if (num == 3){
		cout << "Error: \"" << issue << "\" is not a valid expression" << endl;
	}
	else if (num == 4){
		cout << "Error: \"" << issue << "\" is an unsupported type" << endl;
	}
	else if (num == 5){
		cout << "Error: \"" << issue << "\" is an array and must use a subscript on print" << endl;
	}
	else if (num == 6){
		cout << "Error: \"" << issue << "\" is out of range" << endl; 
	}
	else if (num == 7){
		cout << "Error: return is not allowed in do{ function." << endl;
	}
	else if (num == 8){
		cout << "Error: \"" << issue << "\" is not a value." << endl;
	}
	else if (num == 9){
		cout << "Error: \"" << issue << "\" is not the correct type." << endl;
	}
	else if (num == 10){
		cout << "Error: variable used in 'sys' command is of type " << issue << " and should be a str." << endl;
	}
	else if (num == 11){
		cout << "Error: failed to open \"" << issue << "\". Couldn't find file." << endl; 
	}
	else if (num == 12) {
		cout << "Error: Variable \"" << issue << "\" not found." << endl;
	}
	exit(0);
}
