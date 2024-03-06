file(GLOB SRC
	"*.h"
	"*.cpp"
)

add_library(squirrel)
target_sources(squirrel PRIVATE ${SRC})

set_target_properties(squirrel 
	PROPERTIES
		OUTPUT_NAME "squirrel3"
)

target_link_libraries(squirrel
	PUBLIC
		squirrel_headers
)