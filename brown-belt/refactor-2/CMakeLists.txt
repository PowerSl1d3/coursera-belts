cmake_minimum_required(VERSION 3.17)
project(refactor_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(refactor_2 main.cpp stats_aggregator.h stats_aggregator.cpp stats_aggregator_test.cpp test_runner.h)