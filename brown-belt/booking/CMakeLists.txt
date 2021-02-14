cmake_minimum_required(VERSION 3.17)
project(booking)

set(CMAKE_CXX_STANDARD 17)

add_executable(booking main.cpp test_runner.h old_booking_providers.h old_trip_manager.h new_booking_providers.h new_trip_manager.h booking.h)