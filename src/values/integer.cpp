#include "../core/stsclasses.h"

string runfile(string name, string operation) {
    string *cmd = new string("echo `" + name + " " + operation + "` > output.log");
	system(cmd->c_str());
    delete cmd;
	
	std::ifstream command;
    command.open("./output.log");
    
    string output;
    
    while (!command.eof()) {
        output.push_back(command.get());
    }

    command.close();
    cout << output << '\n';

	return output;
}

stsvars sts::math(int *y) {
    /*
    runs the stormscript file that performs math operations
    */
    string *args = new string(prs[*y] + " " + prs[*y+1] + " " + prs[*y+2]);
    stsvars v;

    if (prs[*y+1].find("+")!=string::npos) {
        v.valint = std::stoi(runfile("math.sts", *args));
        
        v.type = 'i';
    }

    delete args;
    // Let's make pointer deletion a habit 
    return v;
}