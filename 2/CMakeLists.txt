cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 20)

add_executable(main2 src/main2.cpp inc/main2.hpp)
target_link_libraries(main2 PUBLIC genNames)
target_include_directories(main2 PUBLIC inc)