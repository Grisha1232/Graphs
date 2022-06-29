cmake_minimum_required(VERSION 3.21)
project(PeerGradeGraphs)

set(CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -O3")

add_executable(PeerGradeGraphs main.cpp InputMethods.cpp InputMethods.h WorkWithGraphs.cpp WorkWithGraphs.h Graph.cpp Graph.h TransformGraphs.cpp TransformGraphs.h)
