#include "../stormscript.h"
#include "../sts_files.h"
#include "../interpreter/sts_interpreter.h"
#include <fstream>

void stsread(char *argv[], int argc) {
	std::ifstream file;
	string contents;

	prg = {};
	
	int sizeoff = 0;

	file.open(program.filename.c_str());

	if (file.fail()) 
		error(0, program.filename);

	char c = file.get();
	
	while (file.good()) {
		contents += c;
		c = file.get();
	}

	file.close();

	for (int x = 0; x <= contents.size(); x++) {
		if (contents[x] == '\n')
			sizeoff++;
	} //create sizeof in lines

	sizeoff++;
	prg.resize(sizeoff); //create vector for lines
	int loc = 0;
	int a = 0;
	for (int x = 0; x <= contents.size(); x++) {
		if (contents[x] == '\n') {
			for (int y = loc; y < x; y++)
				prg[a] += contents[y]; //add lines to vector

			a++;
			loc = x + 1;
		}
	}
	for (int x = loc; x <= contents.size(); x++)
		prg[prg.size() - 1] += contents[x];  //add last line to vector

	interp(sizeoff, argv, argc);
}
