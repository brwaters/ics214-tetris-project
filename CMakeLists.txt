cmake_minimum_required(VERSION 3.13)
project(FinalProject)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

add_executable(FinalProject main.cpp Point.cpp Point.h Tetromino.cpp Tetromino.h GameBoard.cpp GameBoard.h GridTetromino.cpp GridTetromino.h TetrisGame.cpp TetrisGame.h)

if(SFML_FOUND)
    include_directories(${SFML_INLCUDE_DIR})
    target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
endif()