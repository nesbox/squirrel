file(GLOB SRC
	"*.h"
	"*.cpp"
)

add_library(sqstdlib)
target_sources(sqstdlib PRIVATE ${SRC})

set_target_properties(sqstdlib 
	PROPERTIES
		OUTPUT_NAME "sqstdlib3"
)

target_link_libraries(sqstdlib
	PUBLIC
		squirrel
)