cmake_minimum_required(VERSION 3.20)
project(CMAC)

set(CMAKE_CXX_STANDARD 11)

add_executable(CMAC main.cpp CMAC.cpp CMAC.h dataKit.cpp dataKit.h readAndWrite.cpp)
