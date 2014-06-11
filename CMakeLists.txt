cmake_minimum_required(VERSION 2.6)
project(Tachyon)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -fno-rtti -Wall -Wextra")

include_directories(${CMAKE_SOURCE_DIR}/src)

file(GLOB G1_SRC ${CMAKE_SOURCE_DIR}/src/gen1/*.cxx)

set(SRC
	${CMAKE_SOURCE_DIR}/src/main.cxx
	${CMAKE_SOURCE_DIR}/src/base.cxx
	${CMAKE_SOURCE_DIR}/src/gen-gb.cxx
	${CMAKE_SOURCE_DIR}/src/gen2.cxx
	${CMAKE_SOURCE_DIR}/src/gen3.cxx
)

add_executable(ptxn ${G1_SRC} ${SRC})
