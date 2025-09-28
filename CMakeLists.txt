cmake_minimum_required(VERSION 3.21)

project(squirrel
	VERSION 3.2
	HOMEPAGE_URL "http://squirrel-lang.org/"
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(SQ_GENERATE_SQUIRREL "This option generates squirrel project. By default this option is set to ON" ON)
option(SQ_GENERATE_STDLIB "This option generates squirrel stdlib project. By default this option is set to ON" ON)
option(SQ_GENERATE_COMPILER "This option generates squirrel script compiler. By default this option is set to ON" ON)
option(SQ_GENERATE_INTERPRETER "This option generates squirrel interpreter project. By default this option is set to ON" ON)
option(SQ_GENERATE_WASM_INTERPRETER "This option generates squirrel WebAssembly interpreter project. By default this option is set to ON" ON)
option(SQ_GENERATE_ETC "This option generates squirrel embedding example project. By default this option is set to OFF" OFF)

add_subdirectory(include)

if (SQ_GENERATE_SQUIRREL)
	add_subdirectory(squirrel)
endif()

if (SQ_GENERATE_STDLIB)
	add_subdirectory(sqstdlib)
endif()

if (SQ_GENERATE_COMPILER)
	add_subdirectory(sq_compiler)
endif()

if (SQ_GENERATE_INTERPRETER)
	add_subdirectory(sq)
endif()

if (SQ_GENERATE_WASM_INTERPRETER)
	add_subdirectory(sq_wasm)
endif()

if (SQ_GENERATE_ETC)
	add_subdirectory(etc)
endif()