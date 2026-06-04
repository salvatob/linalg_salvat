#add_executable(vector2_tests
#        test_vector2.cpp
#        test_matrix.cpp
#)
#
#target_link_libraries(vector2_tests
#        PRIVATE
#        linalg_core
#)

include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.3
)

FetchContent_MakeAvailable(Catch2)

add_executable(linalg_tests
        test_matrix.cpp
)

target_link_libraries(linalg_tests
        PRIVATE
        linalg_core
        Catch2::Catch2WithMain
)

include(CTest)

include(Catch)

catch_discover_tests(linalg_tests)
