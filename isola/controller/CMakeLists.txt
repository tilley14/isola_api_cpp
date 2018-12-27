# CMakeList.txt : CMake project for isola, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CONTROLLER_SOURCES "gamecontroller.cpp"
					   "gamecontroller.h"
					   )

# Add source to this project's executable.
add_library(controller ${CONTROLLER_SOURCES})

# TODO: Add tests and install targets if needed.
target_link_libraries(controller model)
