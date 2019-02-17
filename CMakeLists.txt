cmake_minimum_required (VERSION 2.6)
project (StormScript)
set (CMAKE_CXX_FLAGS "--std=c++17")
add_executable(stormscript
    src/core/stormscript.cc
    src/core/set.cc
    src/core/errors.cc
    src/parser/parse.cc
    src/parser/read.cc
    src/parser/mods.cc
    src/interpreter/globscope.cc
    src/interpreter/exec.cc
    src/stream/io.cc
    src/stream/stsstream.cc
    src/stream/loops.cc
    src/stream/files.cc
    src/values/stsdec.cc
    src/values/man.cc
    src/values/if.cc
    src/values/getvals.cc
    src/values/runfunc.cc
    src/values/compare.cc
    src/values/operations.cc
    src/classes/dectype.cc
    src/classes/decmethod.cc)
set (StormScript_VERSION_MAJOR 0)
set (StormScript_VERSION_MINOR 6)
install(TARGETS stormscript RUNTIME DESTINATION bin/)