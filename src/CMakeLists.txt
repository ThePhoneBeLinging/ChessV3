cmake_minimum_required(VERSION 3.31)
project(ChessV3)

set(CMAKE_CXX_STANDARD 20)

add_executable(ChessV3 main.cpp
        Move.h
        Pieces.h
        Board.cpp
        Board.h
)
