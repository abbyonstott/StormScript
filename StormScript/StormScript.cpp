#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>

using std::string;
using std::cout;
using std::endl;

class sts 
{
	int lineon;
	unsigned int sizeoff = 0;
	void out(string str);
	void readline(string prg[], int big);
	string svar_name = ""; //name of string
	string ivar_name = ""; //name of integer
	string svar_cont = ""; //contents of string
	int ivar_cont; //contents of integer
	string sivar_cont; //contents of ivar as string
	int var_num = 0; //number of variables
public:
	string line;
	void error(int num, string issue);	
	void read(string filename);
};

void sts::read(string filename) {
	std::ifstream file;
	string contents;
	file.open(filename, std::ifstream::in);
	char c = file.get();

	while (file.good())
	{
		contents += c;
		c = file.get();
	}
	file.close();

	for (int x = 0; x <= size(contents); x++)
	{
		if (contents[x] == '\n')
		{
			sizeoff++; 
		}
	} //create sizeof in lines

	sizeoff++;
	std::vector<string> prg(sizeoff); //create vector for lines
	int loc = 0;
	int a = 0;

	for (int x = 0; x <= size(contents); x++)
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
	for (int x=loc; x <= size(contents); x++) {
		prg[size(prg)-1] += contents[x];
	} //add last line to vector

	string progm[10000]; //will change to something that doesn't limit lines

	for (int x = 0; x <= sizeoff-1; x++) {
		progm[x] = prg[x];
	}

	readline(progm,sizeoff-1);
}

void sts::readline(string prg[],int big) {
	std::vector<string> vars(big + 1);

	for (int x = 0; x <= big; x++) 
	{
		string l = prg[x];
		string varval;

		for (int y = 0; y < size(l); y++) {
			int z = y + 4;
			if ((l[y] == 'o') && (l[y + 1] == 'u') && (l[y + 2] == 't')) { //checks if command is out
				string str=""; //string to print
				string varnm = ""; //variable name to print

				while (l[z] != ';') {
					if (l[z] == '"') {

						z++;

						while (l[z] != '"') {
							str += l[z];
							z++;
						}

						z++;
						out(str);
					}
					
					else {
						int n = y + 4;

						while (l[n] != ';') {
							varnm += l[n];
							n++;
						}

						string varname;
						int b = 0;
						while (varname != varnm) {
							string var = ""; //variable contents

							try { //checks if svars has position b
								var = vars.at(b);
								var = vars[b];
							}
							catch (const std::out_of_range& m) { //catches error if it doesn't
								error(0, varnm);
							}

							varname = "";
							varval = "";
							int a = 0;
							try { //out str
								while (var[a] != ':') {
									varname += var[a];
									a++;
								}

								a++;

								while (var[a] != '"') {
									varval += var[a];
									a++;
									if (var[a] == ';') {
										a = 0;
										varname = "";
										varval = "";
										throw std::out_of_range("int");
									}
								}

							}
							catch (const std::out_of_range& e) { //out int
								try {
									while (var[a] != ':') {
										varname += var[a];
										a++;
									}
									a++;

									while (var[a] != ';') {
										varval += var[a];
										a++;
									}
								}
								catch (const std::out_of_range& l) {
									error(0, varnm);
								}
							}
						b++;
						}
						str = varval;
						out(str);
						break;
					}
				}
			}
			else if ((l[y] == 's') && (l[y + 1] == 't') && (l[y + 2] == 'r')) { //if str
				svar_cont = "";
				svar_name = "";

				while (l[z] != ':') {
					svar_name += l[z]; //add char to var name
					z++;
				}

				z += 2;

				if (svar_name != "") { //if name isn't blank
					if (l[z] == '"') {
						z++;

						while (l[z] != '"'){
							svar_cont += l[z]; //l[z] to variable cont
							z++;
						}

						svar_cont += l[z];
					
					}
					
					vars.resize(var_num+1);
					vars[var_num] += svar_name+":"+svar_cont;
					var_num++;
				}
				else {
					error(1, "");
				}
			}
			else if ((l[y] == 'i') && (l[y + 1] == 'n') && (l[y + 2] == 't')) {
				ivar_name = "";
				string ivar_conts = "";

				while (l[z] != ':') {
					ivar_name += l[z];
					z++;
				}

				z += 2;
				if (ivar_name != "") {
					while (l[z] != ';') {
						ivar_conts += l[z];
						z++;
					}
					ivar_conts += l[z];
					for (int m = 0; m <= size(ivar_conts)-1; m++) {
						if ((std::isdigit(ivar_conts[m]) / 4 == true) or (ivar_conts[m]==';')) {
							sivar_cont += ivar_conts[m];
						}
						else {
							error(3, ivar_name);
						}
					}

					vars.resize(var_num+1);
					vars[var_num] = ivar_name + ":" + sivar_cont;
					var_num++;

				}
				else {
					error(2, "");
				}
			}
		}
	}
}

void sts::error(int num, string issue) {
	if (num == 0) {
		cout << "Error: No variable named \"" << issue << "\"." << endl;
	}
	else if (num == 1) {
		cout << "Error: string variable must have name" << endl;
	}
	else if (num == 2) {
		cout << "Error: integer variable must have name" << endl;
	}
	else if (num == 3) {
		cout << "Error: integer \"" << issue << "\" must be a number" << endl;
	}	
	else if (num == 4) {
		cout << "Error: No input files" << endl;
	}
	cout << "Press any key to exit...";
	getchar();
	exit(0);
}

void sts::out(string str) {
	cout << str << endl;
}

int main(int argc, char *argv[])
{	
	sts script;

	if (argc!=1) {
		script.read(argv[1]);
	}
	else {
		script.error(4,"");
	}

	cout << "Press any key to exit...";
	getchar();
	return 0;
}