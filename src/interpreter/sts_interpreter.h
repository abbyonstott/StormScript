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
	
	sleep(std::stoi(getval().val));
	
	program.loc--;
}

inline void sys() {
	program.loc++;

	system(getval().val.c_str());

	program.loc++;
}

#endif // INTERPRETER_H_

