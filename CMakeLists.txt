cmake_minimum_required(VERSION 3.29)
project(CSR C)

set(CMAKE_C_STANDARD 11)

add_executable(CSR main.c
        logLib.c
        logLib.h)
