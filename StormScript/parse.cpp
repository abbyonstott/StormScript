#include "stsclasses.h"

string cmd(string line){
    string full;
    int x = 0;

    while ((line[x]!=' '))
    {
        if ((line[x]=='{') || (line[x]==';')) {break;}
        if ((line[x]=='\t')) 
        {
            x++;
            continue;
        }
        full += line[x];
        x++;
    }

    return full;
}

void sts::readline(string prg[], int psize) {
    std::vector<string> ln(psize); // create vector of line commands
    int lnon;

    for (int line = 0; line<=psize-1; line++) {
        ln[line]=cmd(prg[line]);
    }

    for (int line = 0; line<=psize-1; line++) {
        if (ln[line]=="do") {
            lnon=line+1;
            while (ln[lnon]!="}end") {
                if (ln[lnon] == "out") {
                    string print = "";
                    int ch = 5;

                    while (prg[lnon][ch]!=';') {
                        print+=prg[lnon][ch]; // add thing to print to print variable
                        ch++;
                    }

                    out(print); // call out(located in stsstream)
                }
                if (ln[lnon] == "str") {
                    string str = "";
                    string name = "";
                    varnames.resize(varnames.size()+1);
                    int ch = 5;

                    while (prg[lnon][ch]!=':') {
                        name+=prg[lnon][ch];
                        ch++;
                    }
                    ch+=2;
                    varnames[varnames.size()-1]=name;

                    while (prg[lnon][ch]!=';'){
                        str+=prg[lnon][ch];
                        ch++;
                    }
                    
                    decvar(str, 's');
                }
                lnon++;
            }
        }
    }
}

void sts::error(int num, string issue)
{
	if (num == 0)
	{
		cout << "Error: No variable named \"" << issue << "\"." << endl;
	}
	else if (num == 1)
	{
		cout << "Error: string variable must have name" << endl;
	}
	else if (num == 2)
	{
		cout << "Error: integer variable must have name" << endl;
	}
	else if (num == 3)
	{
		cout << "Error: integer \"" << issue << "\" must be a number" << endl;
	}
	else if (num == 4)
	{
		cout << "Error: No input files" << endl;
	}
	cout << "Press return to exit...";
	getchar();
	exit(0);
}