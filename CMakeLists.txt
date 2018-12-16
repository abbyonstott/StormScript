cmake_minimum_required (VERSION 2.6)
project (StormScript)
set (CMAKE_CXX_FLAGS "--std=c++11")
add_executable(stormscript
    src/core/stormscript.cpp
    src/core/set.cpp
    src/core/errors.cpp
    src/core/runlibfunc.cpp
    src/parser/parse.cpp
    src/parser/read.cpp
    src/parser/modules.cpp
    src/interpreter/globscope.cpp
    src/interpreter/exec.cpp
    src/stream/io.cpp
    src/stream/stsstream.cpp
    src/values/stsdec.cpp
    src/values/man.cpp
    src/values/if.cpp
    src/values/getvals.cpp
    src/values/runfunc.cpp
    src/classes/dectype.cpp
    src/classes/decmethod.cpp)
set (StormScript_VERSION_MAJOR 0)
set (StormScript_VERSION_MINOR 3)
install(TARGETS stormscript RUNTIME DESTINATION bin/)
