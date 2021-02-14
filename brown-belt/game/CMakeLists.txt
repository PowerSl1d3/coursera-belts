cmake_minimum_required(VERSION 3.17)
project(game)

set(CMAKE_CXX_STANDARD 17)

add_executable(game main.cpp geo2d.h geo2d.cpp game_object.h test_runner.h)