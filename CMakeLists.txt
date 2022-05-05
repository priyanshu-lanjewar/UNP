cmake_minimum_required(VERSION 3.21)
project(UNP C)

set(CMAKE_C_STANDARD 99)

add_executable(UNP01 main.c)
add_executable(UNP02 001client.c)
add_executable(UNP03 001server.c)
