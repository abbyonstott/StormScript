#pragma once
#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "../stormscript.h"

void newScope();
void runBuiltin();
void runUnknown();
void interp(int psize, char *argv[], int argc);

void forloop();
void whileloop();

// these are defined here because there is nowhere else to put them
inline void wait() {
	program.loc++;
	#if PLATFORM == 1
		Sleep(std::stoi(getval()).val) * 1000);
	#else
		sleep(std::stoi(getval().val));
	#endif
	program.loc--;
}

inline void sys() {
	program.loc++;

	system(getval().val.c_str());

	program.loc++;
}

#endif // INTERPRETER_H_

