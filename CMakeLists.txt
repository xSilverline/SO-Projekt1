cmake_minimum_required(VERSION 3.28)
project(Projekt1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -static")

add_executable(Projekt1 source/class/main.cpp
        source/class/Philosopher.cpp
        source/headers/Philosopher.h
)
