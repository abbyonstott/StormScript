#include "sts_values.h"
#include <random>
#include <ctime>

int genrandomintfromrange() {
	long int ut = static_cast<long int> (time(NULL)); // cast unix epoch to long int
	int range[2]; // range will store the min and max values

	program.loc++;

	std::vector<expression> expressions = program.expressions;

	std::random_device randomd;

	std::mt19937_64 generate(randomd());

	range[0] = std::stoi(getval().val);
	program.loc++;
	range[1] = std::stoi(getval().val);

	std::uniform_int_distribution<> dis(range[0], range[1]);

	return dis(generate);
}

bool randombool() {
	std::random_device randomd;

	std::mt19937_64 generate(randomd());
	std::uniform_int_distribution<> dis(0, 1);
	return dis(generate);
}
