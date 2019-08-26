cmake_minimum_required (VERSION 2.6)
project (StormScript)
set (CMAKE_CXX_FLAGS "--std=c++17")

if (MINGW)
	set (CMAKE_CXX_FLAGS "--std=c++17 -static -static-libgcc -static-libstdc++")
endif (MINGW)

add_executable(stormscript
	src/stormscript.cc
	src/operations.cc
	src/errors.cc
	src/interpreter/interpret.cc
	src/interpreter/newscope.cc
	src/interpreter/loops.cc
	src/networking/stsSocket.cc
	src/parser/parse.cc
	src/parser/read.cc
	src/parser/eval.cc
	src/parser/parseerrors.cc
	src/parser/modules.cc
	src/stream/io.cc
	src/stream/files.cc
	src/type/type.cc
	src/type/objectmember.cc
	src/values/stsdec.cc
	src/values/if.cc
	src/values/find.cc
	src/values/getvals.cc
	src/values/runfunc.cc
	src/values/compare.cc
	src/values/random.cc
)

if (MINGW)
	target_link_libraries(stormscript wsock32 ws2_32)
endif (MINGW)

set (StormScript_VERSION_MAJOR 1)
set (StormScript_VERSION_MINOR 0)
install(TARGETS stormscript RUNTIME DESTINATION bin/)