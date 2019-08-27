#include "stormscript.h"

void error(int num, string issue) { 
	// in order for errors to work stormscript has to be in PATH, but we can assume that it is installed to usr/bin
	string cmd;

	#if (PLATFORM)
	cmd = "stormscript errors.sts ";
	#else
	cmd = "stormscript /usr/share/stormscript/errors.sts ";
	#endif

	cmd += std::to_string(num);
	cmd += " ";
	cmd += issue;
	system(cmd.c_str());
	exit(1);
}