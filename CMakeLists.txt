cmake_minimum_required(VERSION 3.21)
project(jimp_lmp8 C)

set(CMAKE_C_STANDARD 90)

add_executable(jimp_lmp8 alex.c alex.h fun_stack.h parser.c)
