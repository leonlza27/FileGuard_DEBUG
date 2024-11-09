cmake_minimum_required(VERSION 3.28)
project(StrHashMap)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DDBG_ANSI)

add_executable(StrHashMap main.cpp
        FileNodeHash.cpp
        FileNodeHash.h)
