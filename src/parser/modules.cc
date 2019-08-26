#include "../stormscript.h"
#include "../sts_files.h"
#include "sts_parser.h"

void importModules() {
	/*
	* Importing a module works the same way as executing a normal program.
	* (Why should it be any different?)
	* 
	* Instead of being called, modules are actually just added to the parsed version of
	* the original program. This saves time as in this case the module only has to be opened
	* once during a single run
	*/
	program.loc++;

	int endexprloc = 0;

	while (program.expressions[endexprloc].t != ENDEXPR) endexprloc++;

	while (program.loc < endexprloc) {
		if (program.expressions[program.loc].tktype != COMMA) {
			string modname, _filename; // filename adds .sts to the end of the modname
			modname = program.expressions[program.loc].contents;
			_filename = modname + ".sts";

			program_t program_old = program;

			program.loc = 0;
			program.expressions.clear();

			program.filename = _filename;
			stsread({}, 0); // stsread() is run without argv

			program.expressions.insert(program_old.expressions.begin() + endexprloc + 1,
				program.expressions.begin(), program.expressions.end());
			
			program = program_old;
		}

		program.loc += 1;
	}

}
