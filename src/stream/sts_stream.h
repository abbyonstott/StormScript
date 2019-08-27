#pragma once
#ifndef STS_STREAM_H_
#define STS_STREAM_H_

#include "../stormscript.h"
#include <fstream>

// files.cc
void writefile();
stsvars readfile();

// io.cc
string print();
stsvars in();

#endif // STS_STREAM_H_