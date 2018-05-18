#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>
#include <cstdlib>
#include "stsclasses.h"

#if defined(__linux__) // any linux distribution
#define PLATFORM "linux"
#elif defined(_WIN32) // any windows system
#define PLATFORM "windows"
#else //other: please compile if you are on mac. The stormscript.out file was compiled in a linux terminal and therefore is not compatible with mac
#define PLATFORM "other"
#endif

using std::cout;
using std::endl;
using std::string;

//sts Functions

void sts::read(string filename)
{
	std::ifstream file;
	string contents;
	file.open(filename.c_str());
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
	std::vector<string> prg(sizeoff); //create vector for lines
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

	string progm[10000]; //will change to something that doesn't limit lines

	for (int x = 0; x <= sizeoff - 1; x++)
	{
		progm[x] = prg[x];
	}
	for (int x = 0; x <= sizeoff - 1; x++)
	{
		if ((prg[x] == "do{") && (fin == false))
		{
			while (fin == false)
			{
				fin = readline(progm, sizeoff - 1);
			}
		}
	}
}

bool sts::readline(string prg[], int big)
{

	for (int x = 0; x <= big; x++)
	{
		string l = prg[x];
		string varval;

		for (int y = 0; y < l.size(); y++)
		{
			int z = y + 4;
			if ((l[y] == 'o') && (l[y + 1] == 'u') && (l[y + 2] == 't'))
			{					   //checks if command is out
				string str = "";   //string to print
				string varnm = ""; //variable name to print

				while (l[z] != ';')
				{
					if (l[z] == '"')
					{

						z++;

						while (l[z] != '"')
						{
							str += l[z];
							z++;
						}

						z++;
						out(str);
					}

					else
					{
						int n = y + 4;

						while (l[n] != ';')
						{
							varnm += l[n];
							n++;
						}

						string varname;
						int b = 0;
						while (varname != varnm)
						{
							string var = ""; //variable contents

							try
							{ //checks if svars has position b
								var = vars.at(b);
								var = vars[b];
							}
							catch (const std::out_of_range &m)
							{ //catches error if it doesn't
								error(0, varnm);
							}

							varname = "";
							varval = "";
							int a = 0;
							try
							{ //out str
								while (var[a] != ':')
								{
									varname += var[a];
									a++;
								}

								a++;

								while (var[a] != '"')
								{
									varval += var[a];
									a++;
									if (var[a] == ';')
									{
										a = 0;
										varname = "";
										varval = "";
										throw std::out_of_range("int");
									}
								}
							}
							catch (const std::out_of_range &e)
							{ //out int
								try
								{
									while (var[a] != ':')
									{
										varname += var[a];
										a++;
									}
									a++;

									if (PLATFORM == "windows")
									{
										while (var[a] != ';')
										{
											varval += var[a];
											a++;
										}
									}
									else
									{
										while (var[a] != ';')
										{
											varval += var[a];
											a++;
										}
									}
								}
								catch (const std::out_of_range &l)
								{
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
			else if ((l[y] == 's') && (l[y + 1] == 't') && (l[y + 2] == 'r'))
			{ //if str
				svar_cont = "";
				svar_name = "";

				while (l[z] != ':')
				{
					svar_name += l[z]; //add char to var name
					z++;
				}

				z += 2;

				if (svar_name != "")
				{ //if name isn't blank
					if (l[z] == '"')
					{
						z++;

						while (l[z] != '"')
						{
							svar_cont += l[z]; //l[z] to variable cont
							z++;
						}

						svar_cont += l[z];
					}

					vars.resize(var_num + 1);
					vars[var_num] += svar_name + ":" + svar_cont;
					var_num++;
				}
				else
				{
					error(1, "");
				}
			}
			else if ((l[y] == 'i') && (l[y + 1] == 'n') && (l[y + 2] == 't'))
			{
				ivar_name = "";
				string ivar_conts = "";

				while (l[z] != ':')
				{
					ivar_name += l[z];
					z++;
				}

				z += 2;
				if (ivar_name != "")
				{
					while (l[z] != ';')
					{
						ivar_conts += l[z];
						z++;
					}
					ivar_conts += l[z];
					for (int m = 0; m <= ivar_conts.size() - 1; m++)
					{
						if ((std::isdigit(ivar_conts[m]) / 4 == true) or (ivar_conts[m] == ';'))
						{
							sivar_cont += ivar_conts[m];
						}
						else
						{
							cout << ivar_conts << endl;
							error(3, ivar_name);
						}
					}
					vars.resize(var_num + 1);
					vars[var_num] = ivar_name + ":" + sivar_cont;
					var_num++;
				}
				else
				{
					error(2, "");
				}
			}

			else if ((l[y] == 'l') && (l[y + 1] == 'i') && (l[y + 2] == 'b'))
			{
				string libname;

				while (l[z] != ';')
				{
					libname += l[z];
					z++;
				}

				libname = libname + ".stslib";

				read(libname);
			}

			else if ((l[y] == '}') && (l[y + 1] == 'e') && (l[y + 2] == 'n') && (l[y + 3] = 'd') && (l[y + 4] == ';'))
			{
				return true;
			}

			else if ((l[y] == '}') && (l[y + 1] == 'l') && (l[y + 2] == 'o') && (l[y + 3] = 'o') && (l[y + 4] == 'p'))
			{
				z += 2;
				if (times == 0)
				{
					while (l[z] != ')')
					{
						timesstr += l[z];
						z++;
					}
					times = std::stoi(timesstr);
				}
				else
				{
					times--;
				}
				if (times != 1)
				{
					return false;
				}
				else
				{
					return true;
				}
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
	cout << "Press any key to exit...";
	getchar();
	exit(0);
}

void sts::out(string str)
{
	cout << str << endl;
}

int main(int argc, char *argv[])
{
	sts script;

	if (argc != 1)
	{
		script.read(argv[1]);
	}
	else
	{
		script.error(4, "");
	}

	cout << "Press any key to exit...";
	getchar();
	return 0;
}