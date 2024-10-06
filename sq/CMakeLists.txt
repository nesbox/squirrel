if (NOT DEFINED EMSCRIPTEN)
	add_executable(sq "sq.c")

	target_link_libraries(sq 
		PRIVATE
			squirrel
			sqstdlib
	)
endif()