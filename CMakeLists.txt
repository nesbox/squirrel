cmake_minimum_required(VERSION 3.21)

project(squirrel
	VERSION 3.2
	HOMEPAGE_URL "http://squirrel-lang.org/"
)

option(SQ_GENERATE_SQUIRREL "This option generates squirrel project. By default this option is set to ON" ON)
option(SQ_GENERATE_STDLIB "This option generates squirrel stdlib project. By default this option is set to ON" ON)
option(SQ_GENERATE_INTERPRETER "This option generates squirrel interpreter project. By default this option is set to OFF" OFF)
option(SQ_GENERATE_ETC "This option generates squirrel embedding example project. By default this option is set to OFF" OFF)

add_subdirectory(include)

if (SQ_GENERATE_SQUIRREL)
	add_subdirectory(squirrel)
endif()

if (SQ_GENERATE_STDLIB)
	add_subdirectory(sqstdlib)
endif()

if (SQ_GENERATE_INTERPRETER)
	add_subdirectory(sq)
endif()

if (SQ_GENERATE_ETC)
	add_subdirectory(etc)
endif()