cmake_minimum_required(VERSION 3.17)
project(zoo)

set(CMAKE_CXX_STANDARD 17)

add_executable(zoo main.cpp test_runner.h animals.h)