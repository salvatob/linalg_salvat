cmake_minimum_required(VERSION 3.20)

project(linalg_salvat LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)





add_subdirectory(linalg_cpp)
enable_testing()


option(BUILD_BINDING "Build Python bindings" ON)
if(BUILD_BINDING)
    add_subdirectory(bindings)
endif()

# for the Catch2 framework
