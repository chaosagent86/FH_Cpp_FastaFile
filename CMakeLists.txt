cmake_minimum_required(VERSION 3.28)
project(fasta_softwareentwicklung)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(fasta_softwareentwicklung
        dna_related_stuff.cpp
        dna_related_stuff.h
        main.cpp
        protein_related_stuff.cpp
        protein_related_stuff.h
        sequences_analyze.cpp
        sequences_analzye.h)
