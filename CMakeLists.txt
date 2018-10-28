cmake_minimum_required (VERSION 2.6)
project (StormScript)
add_executable(sts core/sts.cpp core/parse.cpp stream/io.cpp stream/stsstream.cpp values/stsdec.cpp values/man.cpp)
set (StormScript_VERSION_MAJOR 0)
set (StormScript_VERSION_MINOR 10)
 