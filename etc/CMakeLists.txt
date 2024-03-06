add_executable(sq_embedded "minimal.c")

target_link_libraries(sq_embedded
	PRIVATE
		squirrel
		sqstdlib
)

add_custom_command(TARGET sq_embedded
	POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy
			"${CMAKE_CURRENT_SOURCE_DIR}/test.nut"
			"${CMAKE_CURRENT_BINARY_DIR}/test.nut"
)