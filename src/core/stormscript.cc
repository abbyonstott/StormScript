#include "../include/stormscript.h"

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
	cout << "StormScript 1.0.0 Beta 3\n";
}

void showhelp() {
	cout << "Usage: stormscript [file|options]\n";
	cout << "StormScript is a powerful, open source scripting language for many operating systems.\n\n";
	cout <<  "  -h, --help: display help\n";
	cout << "  --version: show version\n\n";
	// cout << "  install: install a module\n\n";
	printVersion();
	cout << "git: https://github.com/stormprograms/StormScript\n";
	cout << "For documentation, go to https://stormprograms.com/stormscript\n";
}

int main(int argc, char *argv[]) {
	sts script;

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
				script.error(13, "none");
		}
		else
			script.read(argv, argc, argv[1]);
	}
	else
		showhelp();

	return 0;
}
