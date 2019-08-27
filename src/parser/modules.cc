#include "../stormscript.h"
#include "../sts_files.h"
#include "sts_parser.h"

void importModules(int *i) {
	/*
	* Importing a module works the same way as executing a normal program.
	* (Why should it be any different?)
	* 
	* Instead of being called, modules are actually just added to the parsed version of
	* the original program. This saves time as in this case the module only has to be opened
	* once during a single run
	*/
	*i += 1;

	int endexprloc = 0;

	while (program.expressions[endexprloc].t != ENDEXPR) endexprloc++;

	while (*i < endexprloc) {
		if (program.expressions[*i].tktype != COMMA) {
			string modname, _filename; // filename adds .sts to the end of the modname
			modname = program.expressions[*i].contents;
			_filename = modname + ".sts";

			program_t program_old = program;
			program.expressions.clear();

			program.filename = _filename;
			stsread({}, 0); // stsread() is run without argv

			program_old.expressions.insert(program_old.expressions.begin() + endexprloc + 1,
				program.expressions.begin(), program.expressions.end());
			
			program = program_old;
		}

		*i += 1;
	}
	*i += 1;
}
