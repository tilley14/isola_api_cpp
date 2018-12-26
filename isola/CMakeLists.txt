# CMakeList.txt : CMake project for isola, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_subdirectory(model)
# add_subdirectory(view)
add_subdirectory(controller)


set(SOURCES "isola.cpp"
			"isola.h"
			)

# Add source to this project's executable.
add_executable (isola ${SOURCES})

# TODO: Add tests and install targets if needed.
# target_link_libraries(isola model view controller)
target_link_libraries(isola model controller)