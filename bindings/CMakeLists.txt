find_package(Python REQUIRED COMPONENTS Interpreter Development)

set(PYBIND11_FINDPYTHON ON)

execute_process(
        COMMAND ${Python_EXECUTABLE} -m pybind11 --cmakedir
        OUTPUT_VARIABLE pybind11_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(_core
        pybindings.cpp
)

target_link_libraries(_core
        PRIVATE
        linalg_core
)

set_target_properties(_core PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/python/linalg
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/python/linalg
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/python/linalg
)
