cmake_minimum_required(VERSION 3.24)
project(LibSystem C)

set(CMAKE_C_STANDARD 11)

add_executable(LibSystem main.c parse_csv.c parse_csv.h StructsAndMethods.c StructsAndMethods.h HelpFunctions.c HelpFunctions.h output_csv.c output_csv.h config.h)
