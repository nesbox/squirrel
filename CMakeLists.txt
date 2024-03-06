cmake_minimum_required(VERSION 3.21)

project(squirrel
	VERSION 3.2
	HOMEPAGE_URL "http://squirrel-lang.org/"
)

option(SQ_GENERATE_INTERPRETER "This option generates squirrel interpreter project. By default this option is set to OFF" OFF)
option(SQ_GENERATE_ETC "This option generates squirrel embedding example project. By default this option is set to OFF" OFF)

add_subdirectory(include)
add_subdirectory(squirrel)
add_subdirectory(sqstdlib)

if (SQ_GENERATE_INTERPRETER)
	add_subdirectory(sq)
endif()

if (SQ_GENERATE_ETC)
	add_subdirectory(etc)
endif()