if (NOT DEFINED EMSCRIPTEN)
	add_executable(sq_compiler "sq_compiler.cpp")

	target_link_libraries(sq_compiler
		PRIVATE
			squirrel
			sqstdlib
	)
endif()