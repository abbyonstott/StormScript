#include "sts_values.h"
#include <random>
#include <ctime>

#if (PLATFORM)
#include <chrono>
#endif

int genrandomintfromrange() {
	int range[2]; // range will store the min and max values

	program.loc++;

	range[0] = std::stoi(getval().val);
	program.loc++;
	range[1] = std::stoi(getval().val);

	#if (!PLATFORM)

	std::random_device randomd;

	std::mt19937_64 generate(randomd());

	std::uniform_int_distribution<> dis(range[0], range[1]);

	return dis(generate);
	#else
	/*
	 * This most likely uses more CPU than the Linux version, 
	 * but it is the best I can do until MinGW fixes mt19937_64
	*/
	{ // in it's own scope to allow using namespace
		// not a bad idea as long as it is in a scope for only how long it is needed
		using namespace std::chrono;
		nanoseconds timens = duration_cast<nanoseconds>(steady_clock::now().time_since_epoch());
		srand(timens.count());
	}
	return rand() % range[1] + range[0];
	#endif

	return 0;
}

bool randombool() {
	#if (!PLATFORM)
	std::random_device randomd;

	std::mt19937_64 generate(randomd());
	std::uniform_int_distribution<> dis(0, 1);

	return dis(generate);
	#else
	{
		using namespace std::chrono;
		nanoseconds timens = duration_cast<nanoseconds>(steady_clock::now().time_since_epoch());
		srand(timens.count());
	}
	return rand() % 2;
	#endif
	return 0;
}
