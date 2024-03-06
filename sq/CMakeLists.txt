add_executable(sq "sq.c")

target_link_libraries(sq 
	PRIVATE
		squirrel
		sqstdlib
)