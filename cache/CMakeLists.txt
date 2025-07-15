# The minimum required version of CMake to build this project.
cmake_minimum_required(VERSION 3.16)

project(dtl_cache
    VERSION 1.0
    LANGUAGES CXX)

enable_testing()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/util/cmake")

# Add CXX version/standard here. We'll be using C++ 20. The 
# CMAKE_CXX_STANDARD_REQUIRED boolean sets CXX_STANDARD_REQUIRED
# to make sure that the CXX_STANDARD is not allowed to decay to 
# lower version.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# This sets the compiler to g++ 13 which has full support for C++20.
# set(CMAKE_CXX_COMPILER "/usr/bin/g++-13")

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(rooster main.cpp)
target_link_libraries(rooster PRIVATE ${PROJECT_NAME})

add_subdirectory(test)