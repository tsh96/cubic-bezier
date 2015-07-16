cmake_minimum_required(VERSION 3.2)
project(cubic)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp CubicBezier.cpp CubicBezier.h Rect.h Rect.cpp Point.h Point.cpp CircularList.cpp CircularList.h)
add_executable(cubic ${SOURCE_FILES})