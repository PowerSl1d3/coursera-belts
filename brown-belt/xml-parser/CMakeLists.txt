cmake_minimum_required(VERSION 3.17)
project(xml_parser)

set(CMAKE_CXX_STANDARD 17)

add_executable(xml_parser main.cpp xml.cpp xml.h test_runner.h)