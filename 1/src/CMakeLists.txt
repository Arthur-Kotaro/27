cmake_minimum_required(VERSION 3.30)
#project(Audioplayer VERSION 1.0.0 LANGUAGES CXX)


add_executable(main1 src/main1.cpp inc/main1.hpp)
target_include_directories(main1 PUBLIC inc)
