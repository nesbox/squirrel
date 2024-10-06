if (DEFINED EMSCRIPTEN)
	add_executable(sq_wasm "sq_wasm.c")

	target_link_libraries(sq_wasm
		PRIVATE
			sqstdlib
	)

	target_link_options(sq_wasm
		PRIVATE
			-sEXPORTED_FUNCTIONS=_sq_malloc,_sq_free
	)

	add_custom_command(
		TARGET sq_wasm POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy
				"${CMAKE_CURRENT_BINARY_DIR}/sq_wasm.js"
				"${PROJECT_SOURCE_DIR}/doc/source/_static/sq_wasm.js"
			COMMAND ${CMAKE_COMMAND} -E copy
				"${CMAKE_CURRENT_BINARY_DIR}/sq_wasm.wasm"
				"${PROJECT_SOURCE_DIR}/doc/source/_static/sq_wasm.wasm"
			COMMAND ${CMAKE_COMMAND} -E echo "sq_wasm binaries copied to doc/source/_static/"
)
endif()