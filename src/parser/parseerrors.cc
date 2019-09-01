#include "../stormscript.h"
#include "../sts_files.h"

void parseErrors() { 
	/*
	* this function does not parse runtime errors for:
	* a. speed: it is significantly faster to parse unknown command and missing semicolons before the program is run
	* b. there are certain errors that should only be triggered at runtime
	*/
	std::vector<string> globnames;

	// Stores the names of the local variables in the current scope
	std::vector<string> localnames = globnames;

	bool glob = 1;

	for (int i = 0; i < program.expressions.size(); i++) {
		if ((program.expressions[i].line == parserProgram.size() - 1  && i == program.expressions.size()-1) || program.expressions[i + 1].line != program.expressions[i].line) { // this checks if there is no semicolon at the end of line
			if (program.expressions[i].t != ENDEXPR && program.expressions[i].tktype != CLOSEDCURL && program.expressions[i].tktype != OPENCURL) 
				error(1, std::to_string(program.expressions[i].line + 1)); // add 1 to line because line gives index, which always starts at 0
		}
		else if (program.expressions[i].tktype == OPENCURL) {
			glob = 0;
		}
		else if (program.expressions[i].tktype == CLOSEDCURL) {
			glob = 1;
			localnames = globnames;
		}
		else if ((program.expressions[i].t == UNKNOWN && 
			(program.expressions[i-1].btn == FUNCTION || program.expressions[i+1].tktype == COLON || 
			program.expressions[i-1].btn == TYPE ||
			program.expressions[i-1].btn == TYPE_INTEGER || program.expressions[i-1].btn == TYPE_STRING || program.expressions[i-1].btn == TYPE_LIST || program.expressions[i-1].btn == TYPE_STS_BOOL)) || 
			program.expressions[i].btn == CONSTRUCTOR_SCOPE)
		{ // names vector allows names to be "marked" as known program.expressions
			localnames.push_back(program.expressions[i].contents);
			if (program.expressions[i+1].tktype == ARROW) {
				i+= 2;
				while (program.expressions[i].tktype != OPENCURL) {
					if (program.expressions[i].tktype == COMMA) i++;
					
					localnames.push_back(program.expressions[i].contents);

					i++;
				}
				i--;
				glob = 0;
			} 
		}
		else if (program.expressions[i].t == UNKNOWN && program.expressions[i+1].t == UNKNOWN &&  
			std::find(localnames.begin(), localnames.end(), program.expressions[i].contents) != localnames.end()) 
		{
			localnames.push_back(program.expressions[++i].contents);
		}
		else if (program.expressions[i-1].btn == MODULE) {
			/*
			* It's easier to import modules before runtime because it allows
			* for checks to be run on the modules at the same time that they are
			* run on the original program
			*/
			i--;
			importModules(&i);
		}
		else if (program.expressions[i].btn == STSSOCKET) {
			if (program.expressions[++i].t != UNKNOWN) 
				error(11, std::to_string(program.expressions[i].line));
			
			localnames.push_back(program.expressions[i].contents);
			localnames.push_back("family");
			localnames.push_back("address");
			localnames.push_back("port");
			localnames.push_back("success");
			localnames.push_back("sockval");
			localnames.push_back("await");
			localnames.push_back("connect");

			i += 6;
		}
		else if (program.expressions[i].btn == STSIN) {
			i++;
			// in followed by a variable should be accounted for, as it is currently the only unordinary way to define a variable
			switch (program.expressions[i].t) {
				case UNKNOWN:
					localnames.push_back(program.expressions[i].contents);
					break;
				case ENDEXPR:
					error(12, std::to_string(program.expressions[i-1].line));
					break;
				default:
					error(13, program.expressions[i].contents);
					break;	
			}

		}
		else if // written like this to make it more clear what is happening
			(
			(program.expressions[i].t == UNKNOWN && (program.expressions[i+1].t == ENDEXPR || program.expressions[i+1].tktype == ARROW || program.expressions[i+1].tktype == COMMA)) && 
				(localnames.size() == 0 || // if size is 0 it must be an error
					std::find(localnames.begin(), localnames.end(), program.expressions[i].contents) == localnames.end() // true if not in names
				)
			) // make sure it is not a function before throwing unknown command error
		{
			error(3, program.expressions[i].contents);
		}
		
		if (glob) globnames = localnames; // every scope change keeps the previous scope's variables
	}
}