cmake_minimum_required(VERSION 4.2)

project(linalg_salvat LANGUAGES CXX)
#project(linalg_salvat)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_minimum_required(VERSION 3.20)



#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(linalg_cpp)
add_subdirectory(bindings)
