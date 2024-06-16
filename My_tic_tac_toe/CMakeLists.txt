cmake_minimum_required(VERSION 3.00)

# Set the project name
project(My_tic_tac_toe VERSION 1.0) 

# lang standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# include directories
include_directories(include)

# source files
file(GLOB SOURCES "src/*.c")

# Add an executable
add_executable(My_tic_tac_toe ${SOURCES})

# bin directory
set_target_properties(My_tic_tac_toe PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)