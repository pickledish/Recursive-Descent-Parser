cmake_minimum_required(VERSION 3.6)
project(Project_02)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        scanner.c
    productions.txt
    README.md recursiveDescentParser.c scanner.h evaluateParseTree.c tabledriven.c)

add_executable(Project_02 ${SOURCE_FILES})