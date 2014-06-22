cmake_minimum_required(VERSION 2.6)
project(Tachyon)

set(USE_QT ON CACHE BOOL "Build Qt frontend")

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -fno-rtti -Wall -Wextra")

include_directories(${CMAKE_SOURCE_DIR}/src)

file(GLOB G1_SRC ${CMAKE_SOURCE_DIR}/src/gen1/*.cxx)
file(GLOB G2_SRC ${CMAKE_SOURCE_DIR}/src/gen2/*.cxx)
file(GLOB G3_SRC ${CMAKE_SOURCE_DIR}/src/gen3/*.cxx)
file(GLOB GB_SRC ${CMAKE_SOURCE_DIR}/src/gb/*.cxx)
file(GLOB COMMON_SRC ${CMAKE_SOURCE_DIR}/src/common/*.cxx)

add_library(ptxncore ${COMMON_SRC} ${GB_SRC} ${G1_SRC} ${G2_SRC} ${G3_SRC})

set(MAIN_SRC ${CMAKE_SOURCE_DIR}/src/main.cxx)

add_executable(ptxn ${MAIN_SRC})
target_link_libraries(ptxn ptxncore)

if(USE_QT)
	add_subdirectory(${CMAKE_SOURCE_DIR}/src/qt ${CMAKE_BINARY_DIR}/qt)
endif()
