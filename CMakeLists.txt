cmake_minimum_required(VERSION 3.27)
project(CDataFrame C)

set(CMAKE_C_STANDARD 11)

add_executable(CDataFrame
        main.c
        structures.c
        structures.h)
