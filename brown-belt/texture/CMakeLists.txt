cmake_minimum_required(VERSION 3.17)
project(texture)

set(CMAKE_CXX_STANDARD 17)

add_executable(texture main.cpp Textures.h Common.h Textures.cpp Solution.cpp test_runner.h)