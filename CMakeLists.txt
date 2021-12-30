cmake_minimum_required(VERSION 3.21)
project(jimp_lmp8 C)

set(CMAKE_C_STANDARD 90)

set(CMAKE_CURRENT_BINARY_DIR ${CMAKE_SOURCE_DIR})

add_executable(jimp_lmp8 alex_test.c alex.c alex.h fun_stack.h parser.c parser.h fun_stack.c parser.h)


add_executable(jimp_lmp8_fstacktest funstack_test.c fun_stack.h fun_stack.c)