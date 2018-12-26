# CMakeList.txt : CMake project for isola, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(MODEL_SOURCES "player.cpp"
				  "player.h"
				  )

# Add source to this project's executable.
add_library(model ${MODEL_SOURCES})

# TODO: Add tests and install targets if needed.
