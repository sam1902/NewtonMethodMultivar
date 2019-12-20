cmake_minimum_required(VERSION 3.13)
project(NewtonMultivar C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lm")

add_executable(NewtonMultivar main.c Vector.c Vector.h Function.c Function.h FunctionsInit.c FunctionsInit.h Matrix.c Matrix.h)