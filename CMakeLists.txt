cmake_minimum_required(VERSION 3.28)
project(fasta_softwareentwicklung)

set(CMAKE_CXX_STANDARD 17)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Wconversion -Wunused-variable")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

include_directories(.)

add_executable(fasta_softwareentwicklung
        main.cpp
)
