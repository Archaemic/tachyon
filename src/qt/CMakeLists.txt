cmake_minimum_required(VERSION 2.8.8)
project(QTachyon)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(APPLE)
	# Homebrew installs Qt5 here
	set(CMAKE_PREFIX_PATH "/usr/local/opt/qt5")
endif()

find_package(Qt5Widgets REQUIRED)

set(SRC
	Cartridge.cpp
	PokemonTable.cpp
)

add_executable(QTachyon WIN32 MACOSX_BUNDLE main.cpp ${SRC})

qt5_use_modules(QTachyon Widgets)

target_link_libraries(QTachyon ptxncore)
