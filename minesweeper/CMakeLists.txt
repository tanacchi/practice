cmake_minimum_required(VERSION 3.5.1)

add_definitions("-Wall --std=c++14")
add_executable(minesweeper.out
  main.cpp
  PlaneVector.cpp
)
