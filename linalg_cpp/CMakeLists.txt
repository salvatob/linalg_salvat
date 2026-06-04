add_library(linalg_core STATIC
        include/linalg/Matrix.hpp
        src/Matrix.tpp
)

target_include_directories(linalg_core
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Enable warnings
if(MSVC)
    target_compile_options(linalg_core PRIVATE /W4)
else()
    target_compile_options(linalg_core PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_subdirectory(tests)
