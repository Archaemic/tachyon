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
	Cartridge.cxx
	GroupList.cxx
	GameRegistry.cxx
	GameRegistryView.cxx
	PokemonList.cxx
	PokemonSelector.cxx
	PokemonStatus.cxx
	PokemonTable.cxx
	SpriteUtilities.cxx
)

qt5_wrap_ui(UI_SRC
	PokemonStatus.ui
)

add_executable(QTachyon WIN32 MACOSX_BUNDLE main.cxx ${SRC} ${UI_SRC})
set_property(TARGET QTachyon PROPERTY MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/src/qt/Info.plist.in)

qt5_use_modules(QTachyon Widgets)

target_link_libraries(QTachyon ptxncore)
