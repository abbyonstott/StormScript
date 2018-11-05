#include "stsclasses.h"

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

void sts::read(char *argv[], int argc) {
	string filename = argv[1];
	std::ifstream file;
	string contents;
	file.open(filename.c_str());
	if (file.fail()) {
		error(11, filename);
	}
	char c = file.get();
	
	while (file.good())
	{
		contents += c;
		c = file.get();
	}
	file.close();

	for (int x = 0; x <= contents.size(); x++)
	{
		if (contents[x] == '\n')
		{
			sizeoff++;
		}
	} //create sizeof in lines

	sizeoff++;
	prg.resize(sizeoff); //create vector for lines
	int loc = 0;
	int a = 0;
	for (int x = 0; x <= contents.size(); x++)
	{
		if (contents[x] == '\n')
		{
			for (int y = loc; y < x; y++)
			{
				prg[a] += contents[y]; //add lines to vector
			}
			a++;
			loc = x + 1;
		}
	}
	for (int x = loc; x <= contents.size(); x++)
	{
		prg[prg.size() - 1] += contents[x];
	} //add last line to vector

	interp(filename, prg, sizeoff, argv, argc);
}

int main(int argc, char *argv[]) {
	sts script;

	if (argc != 1)
	{
		if (string(argv[1])=="--version"){
			cout << "StormScript v1.0.0-alpha \"Apple 12\"" << endl;
		}
		else if ((string(argv[1])=="--help") || (string(argv[1])=="-h")) {
			cout << "Usage: stormscript [file|options]" << endl;
			cout << "StormScript is an open source scripting language for Linux." << endl;
			cout << endl;
			cout <<  "  -h, --help: display help"<< endl;
			cout << "  --version: show version" << endl;
			cout << "  -l, --library [name]: initialize library" << endl;
			cout << endl;
			system("stormscript --version");
			cout << "git: https://github.com/stormprograms/StormScript" << endl;
			cout << "For documentation, go to https://stormprograms.com/stormscript/docs" << endl;
		}
		else if ((string(argv[1])=="--library") || (string(argv[1])=="-l")){ // check for library
			if (argv[2]!=NULL) {
				string name = string(argv[2]);
				system("echo `curl https://raw.githubusercontent.com/stormprograms/StormScript/master/api/python/download.sh");
			}
			else {
				script.error(13, "");
			}
		}
		else{
			script.read(argv, argc);
		}
	}
	else
	{
		script.error(0, "");
	}

	return 0;
}