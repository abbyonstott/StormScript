#include "../stormscript.h"
#include "sts_stream.h"

stsvars readfile() {
	stsvars v;
	v.type = 's';

	program.loc += 1;

	std::ifstream file;
	string contents;
	string name = getval().val;

	file.open(name);

	if (file.fail()) 
		error(0, name);

	char c = file.get();

	while (file.good()) {
		contents += c;
		c = file.get();
	}

	file.close();

	v.val = contents;

	return v;
}

void writefile() {
	program.loc += 1;
	std::ofstream file;
	string name = getval().val;

	file.open(name);

	program.loc += 1;
	string contents = getval().val;

	file.write(contents.c_str(), contents.size());
	file.close();

	program.loc += 1;
}