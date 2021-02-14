cmake_minimum_required(VERSION 3.17)
project(object_pool)

set(CMAKE_CXX_STANDARD 17)

add_executable(object_pool main.cpp profile.h test_runner.h)