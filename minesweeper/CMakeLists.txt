cmake_minimum_required(VERSION 3.5.1)

add_definitions("-Wall --std=c++14")
include_directories(include)
add_executable(minesweeper.out
  src/main.cpp
  src/PlaneVector.cpp
)
