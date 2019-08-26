#include "stormscript.h"
#include "sts_files.h"

/*
   _____ _                        _____           _       _   
  / ____| |                      / ____|         (_)     | |  
 | (___ | |_ ___  _ __ _ __ ___ | (___   ___ _ __ _ _ __ | |_ 
  \___ \| __/ _ \| '__| '_ ` _ \ \___ \ / __| '__| | '_ \| __|
  ____) | || (_) | |  | | | | | |____) | (__| |  | | |_) | |_ 
 |_____/ \__\___/|_|  |_| |_| |_|_____/ \___|_|  |_| .__/ \__|
                                                   | |        
                                                   |_|         
*/

void printVersion() {
	cout << "StormScript 1.0.0 Release Candidate 2\n";
}

void showhelp() {
	cout << "Usage: stormscript [file|options]\n";
	cout << "StormScript is a powerful, open source programming language for many operating systems.\n\n";
	cout <<  "  -h, --help: display help\n";
	cout << "  --version: show version\n\n";
	cout << "  install: install a module\n\n";
	printVersion();
	cout << "git: https://github.com/stormprograms/StormScript\n";
	cout << "For documentation, go to https://stormscript.dev/docs\n";
}

int main(int argc, char *argv[]) {
	if (argc != 1) {
		if (string(argv[1])=="--version")
			printVersion();
		else if ((string(argv[1])=="--help") || (string(argv[1])=="-h"))
			showhelp();
		else if (string(argv[1])=="install") {
			string cmd = "wget https://storage.googleapis.com/stormscript/";
			if (argc > 2) {
				cmd+= argv[2];
				cmd+= ".sts";
				system(cmd.c_str());
			}
			else
				error(9, "none");
		}
		else {
			program.filename = argv[1];
			stsread(argv, argc);
		}
	}
	else
		showhelp();

	return 0;
}
