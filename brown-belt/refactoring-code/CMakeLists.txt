cmake_minimum_required(VERSION 3.17)
project(refactoring_code)

set(CMAKE_CXX_STANDARD 17)

add_executable(refactoring_code main.cpp json.h xml.h json.cpp xml.cpp test_runner.h)