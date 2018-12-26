# CMakeList.txt : CMake project for isola, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(SOURCES "isola.cpp"
			"isola.h"
			"board.cpp"
			"board.h"
			"player.cpp"
			"player.h")

# Add source to this project's executable.
add_executable (isola ${SOURCES})

# TODO: Add tests and install targets if needed.
