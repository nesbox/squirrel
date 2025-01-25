if (NOT DEFINED EMSCRIPTEN)
	add_executable(sq-compiler "sq-compiler.cpp")

	target_link_libraries(sq-compiler
		PRIVATE
			squirrel
			sqstdlib
	)
endif()