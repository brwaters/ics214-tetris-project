cmake_minimum_required(VERSION 3.10)
project(Tetris)

set(CMAKE_CXX_STANDARD 17)

# Add source files
set(SOURCE_FILES
    Gameboard.cpp
    GridTetromino.cpp
    Point.cpp
    TetrisGame.cpp
    Tetromino.cpp
    main.cpp
)

# Add executable
add_executable(Tetris ${SOURCE_FILES})

# Find SFML
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})

# Link SFML libraries explicitly
target_link_libraries(Tetris sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
