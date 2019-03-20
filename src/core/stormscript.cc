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
	cout << "StormScript v0.7.0 \"Grape\"\n";
}

int main(int argc, char *argv[]) {
	sts script;

	if (argc != 1) {
		if (string(argv[1])=="--version")
			printVersion();
		else if ((string(argv[1])=="--help") || (string(argv[1])=="-h")) {
			cout << "Usage: stormscript [file|options]\n";
			cout << "StormScript is an open source scripting language for Linux.\n\n";
			cout <<  "  -h, --help: display help\n";
			cout << "  --version: show version\n";
			cout << "  install: install a module\n\n";
			system("stormscript --version");
			cout << "git: https://github.com/stormprograms/StormScript\n";
			cout << "For documentation, go to https://stormprograms.com/stormscript/docs\n";
		}
		else if (string(argv[1])=="install") {
			string cmd = "wget https://storage.googleapis.com/stormscript/";
			if (argc > 2) {
				cmd+= argv[2];
				cmd+= ".sts";
				system(cmd.c_str());
			}
			else {
				script.error(13, "none");
			}
		}
		else {
			script.read(argv, argc, argv[1]);
		}
	}
	else {
		printVersion();
		cout << "Try 'stormscript --help' for more information.\n\n";
		script.prg.resize(script.prg.size()+1);
		script.prg[script.prg.size()-1] = "do{\n";
		script.term = true;
		script.interp("", -1, argv, argc);
	}
	return 0;
}
