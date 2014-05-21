cmake_minimum_required(VERSION 2.6)
project(Tachyon)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11")

add_executable(ptxn src/main.cxx src/base.cxx src/gen1.cxx src/gen-gb.cxx)
