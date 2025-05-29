cmake_minimum_required(VERSION 3.31)
project(ChessV3_Tests)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES
        PerftTests.cpp
        PerftTestUtil.cpp
        PerftTestUtil.h
        ../src/Board.cpp
)
add_executable(Chess_Tests ${SOURCES})

target_link_libraries(Chess_Tests PUBLIC
        GTest::gtest
        GTest::gtest_main
)