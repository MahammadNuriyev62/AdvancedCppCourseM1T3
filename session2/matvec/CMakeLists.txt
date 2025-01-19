cmake_minimum_required(VERSION 3.16)

project(templates LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(
  -Wall
  -Wextra
  -Werror
  -Wnull-dereference
  -Wold-style-cast
  -Wdouble-promotion
  -Wshadow)

include_directories(include)

add_executable(matvec matvec.cpp)
