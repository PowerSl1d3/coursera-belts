cmake_minimum_required(VERSION 3.17)
project(ini_parser)

set(CMAKE_CXX_STANDARD 17)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
add_executable(ini_parser main.cpp ini.h ini.cpp test_runner.h)