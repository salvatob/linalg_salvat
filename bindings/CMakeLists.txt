find_package(Python REQUIRED COMPONENTS Interpreter Development)

set(PYBIND11_FINDPYTHON ON)

execute_process(
        COMMAND ${Python_EXECUTABLE} -m pybind11 --cmakedir
        OUTPUT_VARIABLE pybind11_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(linalg
        pybindings.cpp
)

target_link_libraries(linalg
        PRIVATE
        linalg_core
)
