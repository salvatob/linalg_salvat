
include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.3
)

FetchContent_MakeAvailable(Catch2)

add_executable(linalg_tests
        test_main.cpp
        test_matmul_basic.cpp
        test_matmul_edge.cpp
        test_matmul_consistency.cpp
        test_matrix.cpp
        test_matmul_compile_fail.cpp
)

target_link_libraries(linalg_tests
        PRIVATE
        linalg_core
        Catch2::Catch2WithMain
)

#
#include(CTest)
#
#include(Catch)
#
#catch_discover_tests(linalg_tests)

enable_testing()
add_test(NAME linalg_tests COMMAND linalg_cpp/tests/linalg_tests)
