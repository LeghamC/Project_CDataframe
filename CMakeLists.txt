cmake_minimum_required(VERSION 3.27)
project(CDataFrame C)

set(CMAKE_C_STANDARD 11)

add_executable(CDataFrame
        main.c
        column.h
        cdataframe.h
        list.h
        list.c
        matrix.h
        matrix.c
        sort.h
        sort.c
        cdataframe.c
        column.c
        vector.c)
