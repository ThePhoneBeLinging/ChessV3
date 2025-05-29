cmake_minimum_required(VERSION 3.31)
project(ChessV3)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1  # Specify the version you need
)

FetchContent_MakeAvailable(googletest)
add_subdirectory(Tests)
enable_testing()

add_subdirectory(src)