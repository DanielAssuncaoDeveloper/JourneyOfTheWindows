cmake_minimum_required(VERSION 3.29)
project(JourneyOfTheWindows C)

set(CMAKE_C_STANDARD 11)

add_executable(JourneyOfTheWindows main.c
        HeaderFiles/testHeader.h
        Src/TestFile.c)
