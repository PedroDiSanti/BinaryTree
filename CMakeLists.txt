cmake_minimum_required(VERSION 3.17)
project(binary_tree C)

set(CMAKE_C_STANDARD 99)

add_executable(binary_tree main.c)
target_link_libraries(binary_tree m)