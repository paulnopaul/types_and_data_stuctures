cmake_minimum_required(VERSION 3.15)
project(lab_03 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab_03 main.c smatrix.c smatrix.h linked_list.c linked_list.h err.c err.h matrix.c matrix.h)