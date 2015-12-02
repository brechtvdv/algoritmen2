cmake_minimum_required(VERSION 3.3)
project(Shift_andzoekmethode)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp koran.txt shift-and.h shift-and_1.h bitpattern.h)
add_executable(Shift_andzoekmethode ${SOURCE_FILES})