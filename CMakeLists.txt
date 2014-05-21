cmake_minimum_required(VERSION 2.6)
project(Tachyon)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11")

set(SRC
	${CMAKE_SOURCE_DIR}/src/main.cxx
	${CMAKE_SOURCE_DIR}/src/base.cxx
	${CMAKE_SOURCE_DIR}/src/gen-gb.cxx
	${CMAKE_SOURCE_DIR}/src/gen1.cxx
)

add_executable(ptxn ${SRC})
