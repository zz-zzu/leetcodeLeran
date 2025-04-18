cmake_minimum_required(VERSION 3.29)
project(Learn)

set(CMAKE_CXX_STANDARD 11)


set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS "-O0 -g")

add_executable(main_1 main.cpp)
add_executable(main_2 question42.cpp)
add_executable(main_3 question3.cpp)
add_executable(main_4 question438.cpp)
add_executable(main_5 question239.cpp)
add_executable(main_6 二叉树.cpp)
add_executable(main_7 图论.cpp)