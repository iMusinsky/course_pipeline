cmake_minimum_required(VERSION 3.24)
project(course_pipeline)

set(CMAKE_CXX_STANDARD 20)

add_executable(course_pipeline main.cpp pipeline.c++ pipeline.h process.c++ process.h)
