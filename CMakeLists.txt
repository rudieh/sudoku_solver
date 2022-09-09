cmake_minimum_required(VERSION 3.15.0)
project(sudoku_solver 
    VERSION 0.1.0 
    DESCRIPTION "Project to test C++ by solving sudokus"
    LANGUAGES CXX)

include(CTest)
enable_testing()

set(SOURCES main.cpp src/grid.cpp src/subgrid.cpp)
add_executable(sudoku_solver ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
