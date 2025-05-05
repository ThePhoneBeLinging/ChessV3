cmake_minimum_required(VERSION 3.31)
project(Chess)

set(CMAKE_CXX_STANDARD 20)

add_executable(Chess main.cpp
        Move.h
        Pieces.h
        Board.cpp
        Board.h
)
