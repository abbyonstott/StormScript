cmake_minimum_required (VERSION 2.6)
project (StormScript)
set (CMAKE_CXX_FLAGS "--std=c++11")
add_executable(stormscript
    core/stormscript.cpp
    core/set.cpp
    core/errors.cpp
    core/runlibfunc.cpp
    parser/parse.cpp
    interpreter/globscope.cpp
    interpreter/exec.cpp
    stream/io.cpp
    stream/stsstream.cpp
    values/stsdec.cpp
    values/man.cpp
    values/if.cpp
    values/getvals.cpp
    values/runfunc.cpp
    classes/dectype.cpp
    classes/decmethod.cpp)
set (StormScript_VERSION_MAJOR 0)
set (StormScript_VERSION_MINOR 2)
install(TARGETS stormscript RUNTIME DESTINATION bin/)
