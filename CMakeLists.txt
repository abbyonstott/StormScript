cmake_minimum_required (VERSION 2.6)
project (StormScript)
set (CMAKE_CXX_FLAGS "--std=c++17")
if (MINGW)
set (CMAKE_CXX_FLAGS "--std=c++17 -static -static-libgcc -static-libstdc++")
endif (MINGW)
add_executable(stormscript
    src/core/stormscript.cc
    src/parser/parse.cc
    src/parser/read.cc
    src/parser/eval.cc
    src/parser/parseerrors.cc
    src/interpreter/interpret.cc
    src/interpreter/newscope.cc
    src/stream/io.cc
    src/stream/loops.cc
    src/stream/files.cc
    src/values/stsdec.cc
    src/values/if.cc
    src/values/getvals.cc
    src/values/runfunc.cc
    src/values/compare.cc
    src/values/operations.cc
    src/values/random.cc)
set (StormScript_VERSION_MAJOR 1)
set (StormScript_VERSION_MINOR 0)
install(TARGETS stormscript RUNTIME DESTINATION bin/)