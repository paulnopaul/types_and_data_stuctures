cmake_minimum_required(VERSION 3.15)
project(lab_02 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab_02 main.c student.c student.h student_database.c student_database.h date.c date.h errdef.h db_menu.c db_menu.h errdef.c)