#include "stsclasses.h"

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

	string progm[prg.size()];

	for (int x = 0; x <= sizeoff - 1; x++)
	{
		progm[x] = prg[x];
	}
	readline(progm, sizeoff);
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