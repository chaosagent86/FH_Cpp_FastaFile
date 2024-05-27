cmake_minimum_required(VERSION 3.28)
project(fasta_softwareentwicklung)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(fasta_softwareentwicklung
        FASTA_Analysis.h
        FASTA_Analysis.cpp
        DNA.cpp
        DNA.h
        Protein.cpp
        Protein.h
        main.cpp)
