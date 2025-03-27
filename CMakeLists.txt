cmake_minimum_required(VERSION 3.28)
project(Projekt1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Projekt1 source/class/main.cpp
        source/class/Philosopher.cpp
        source/headers/Philosopher.h
)
