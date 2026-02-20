cmake_minimum_required(VERSION 3.16)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 17)

add_executable(Minesweeper
    src/main.cpp
    src/GameEngine.cpp
    src/Board.cpp
    src/Grid.cpp
)
target_include_directories(Minesweeper PUBLIC include)
