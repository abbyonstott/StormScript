#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using std::string;
using std::cout;
using std::endl;

class sts 
{
	int lineon;
	unsigned int sizeoff = 0;
	void error(int num);
	string svar_name = "";
	string svar_cont = "";
	int var_num = 0;
public:
	string line;
	void out(string str);
	void readline(string prg[], int big);
	void read();
};

void sts::read() {
	std::ifstream file;
	string contents;
	file.open("test.sts", std::ifstream::in);
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

	string progm[10000];

	for (int x = 0; x <= sizeoff-1; x++) {
		progm[x] = prg[x];
	}

	readline(progm,sizeoff-1);
}

void sts::readline(string prg[],int big) {
	std::vector<string> svars(big + 1);

	for (int x = 0; x <= big; x++) 
	{
		string l = prg[x];
		string svarval;
		for (int y = 0; y < size(l); y++) {
			if ((l[y] == 'o') && (l[y + 1] == 'u') && (l[y + 2] == 't')) {
				int z = y + 4;
				string str="";
				string strvarnm = "";

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
							strvarnm += l[n];
							n++;
						}

						string svarname;
						int b = 0;
						while (svarname != strvarnm) {

							string svar = svars[b];
							svarname = "";
							svarval = "";
							int a = 0;

							while (svar[a] != ':') {
								svarname += svar[a];
								a++;
							}

							a++;

							while (svar[a] != '"') {
								svarval += svar[a];
								a++;
							}
							b++;
						}
						str = svarval;
						out(str);
						break;
					}
				}
			}
			else if ((l[y] == 's') && (l[y + 1] == 't') && (l[y + 2] == 'r')) {
				svar_cont = "";
				svar_name = "";
				int a = y + 4;
				while (l[a] != ':') {
					svar_name += l[a];
					a++;
				}
				a += 2;
				if (svar_name != "") {
					if (l[a] == '"') {
						a++;
						while (l[a] != '"'){
							svar_cont += l[a];
							a++;
						}
						svar_cont += l[a];
					}
					svars.resize(var_num+1);
					svars[var_num] += svar_name+":"+svar_cont;
					var_num++;
				}
				else {
					error(1);
				}
			}
		}
	}
}

void sts::error(int num) {
	if (num == 0) {
		cout << "Error: Variable Undefined" << endl;
	}
	else if (num == 1) {
		cout << "Error: string variable must have name" << endl;
	}

	exit(0);
}

void sts::out(string str) {
	cout << str << endl;
}

int main()
{	
	sts script;
	script.read();
	system("sleep .1");
	return 0;
} 
