cmake_minimum_required(VERSION 3.6)
project(Laba1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp IniParser.cpp IniParser.h exc_io.h allExceptions.h exc_ini_not_initialized.h exc_ini_not_found.h exc_wrong_type.h main.cpp)
add_executable(Laba1 ${SOURCE_FILES})