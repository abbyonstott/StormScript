cmake_minimum_required (VERSION 2.6)
project (StormScript)
set (CMAKE_CXX_FLAGS "--std=c++11")
add_executable(stormscript
    core/sts.cpp
    core/parse.cpp
    core/set.cpp
    core/errors.cpp
    stream/io.cpp
    stream/stsstream.cpp
    values/stsdec.cpp
    values/man.cpp
    values/if.cpp
    values/getvals.cpp
    classes/dectype.cpp)
set (StormScript_VERSION_MAJOR 1)
set (StormScript_VERSION_MINOR 1)
install(TARGETS stormscript RUNTIME DESTINATION bin/)