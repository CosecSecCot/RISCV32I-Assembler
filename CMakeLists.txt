cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(RISCV-Assembler-and-Simulator VERSION 1.0)
add_executable(a.out main.cpp string_utils.cpp parser.cpp)
target_include_directories(a.out PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/utils)
