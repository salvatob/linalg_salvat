add_executable(vector2_tests
        test_vector2.cpp
)

target_link_libraries(vector2_tests
        PRIVATE
        linalg_core
)

#include(FetchContent)
#
#FetchContent_Declare(
#        Catch2
#        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#        GIT_TAG v3.5.3
#)
#
#FetchContent_MakeAvailable(Catch2)
#
#add_executable(test_vector2
#        test_vector2.cpp
#)
#
#target_link_libraries(test_vector2
#        PRIVATE
#        myproject_core
#        Catch2::Catch2WithMain
#)
#
#include(CTest)
#
#include(Catch)
#
#catch_discover_tests(test_vector2)