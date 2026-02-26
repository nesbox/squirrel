if (NOT DEFINED EMSCRIPTEN)
    add_executable(sq_demo "sq_demo.cpp")

    target_link_libraries(sq_demo
        PRIVATE
            squirrel
            sqstdlib
    )
endif()