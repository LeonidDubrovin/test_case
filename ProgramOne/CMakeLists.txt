cmake_minimum_required(VERSION 3.21)
project(ProgramOne)

set(CMAKE_CXX_STANDARD 14)

if (WIN32)
    link_libraries(ws2_32 wsock32)
endif (WIN32)

include_directories(.)

add_executable(ProgramOne
        main.cpp
        ProgramOne.cpp
        ProgramOne.h Client.cpp Client.h)
