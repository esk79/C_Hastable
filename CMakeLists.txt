cmake_minimum_required(VERSION 3.3)
project(Hashtable)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -std=c99")

set(SOURCE_FILES main.c Hashtable.c Hashtable.h)
add_executable(Hashtable ${SOURCE_FILES})