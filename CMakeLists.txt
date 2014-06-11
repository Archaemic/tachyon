cmake_minimum_required(VERSION 2.6)
project(Tachyon)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -fno-rtti -Wall -Wextra")

include_directories(${CMAKE_SOURCE_DIR}/src)

file(GLOB G1_SRC ${CMAKE_SOURCE_DIR}/src/gen1/*.cxx)
file(GLOB G2_SRC ${CMAKE_SOURCE_DIR}/src/gen2/*.cxx)
file(GLOB G3_SRC ${CMAKE_SOURCE_DIR}/src/gen3/*.cxx)
file(GLOB COMMON_SRC ${CMAKE_SOURCE_DIR}/src/common/*.cxx)

set(SRC
	${CMAKE_SOURCE_DIR}/src/main.cxx
)

add_executable(ptxn ${COMMON_SRC} ${G1_SRC} ${G2_SRC} ${G3_SRC} ${SRC})
