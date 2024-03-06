file(GLOB SRC
	"*.h"
)

add_library(squirrel_headers INTERFACE ${SRC})

target_include_directories(squirrel_headers
	INTERFACE
		"./"
)