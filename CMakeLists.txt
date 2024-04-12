cmake_minimum_required(VERSION 3.28)
project(BFRES_Lib VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)

add_library(BFRES_Lib STATIC
        libSrc/BFRES/BFRES.cpp
        libSrc/BFRES/BFRES.h)
add_library(fileOps STATIC
        libSrc/usefulFunctions/fileOps.cpp
        libSrc/usefulFunctions/fileOps.h)

add_executable(BFRES_Lib_Test
        testSrc/main.h
        testSrc/main.cpp)