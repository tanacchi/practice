cmake_minimum_required(VERSION 3.10.2)

project(
  tetris
  VERSION 0.0.0
  LANGUAGES CXX)

find_package(Curses REQUIRED)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_STANDARD 14)

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
file(GLOB_RECURSE PROJECT_SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*)

include_directories(
  ${PROJECT_INCLUDE_DIR}
  ${CURSES_INCLUDE_DIR})

link_directories(
  ${CURSES_LIBRARY_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
add_executable(${PROJECT_NAME}.out
  ${PROJECT_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}.out
  ${CURSES_LIBRARIES})
