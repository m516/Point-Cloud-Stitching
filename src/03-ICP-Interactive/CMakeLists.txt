# CMakeList.txt : CMake project for CV-Sandbox, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

disable_if_pcl_not_found()

# This is the name of the executable
set(EXECUTABLE_NAME 03_ICP_INTERACTIVE)

# Add source to this project's executable.
add_executable (${EXECUTABLE_NAME} "main.cpp" )

# Add tests and install targets if needed.
TARGET_LINK_LIBRARIES (${EXECUTABLE_NAME} PRIVATE ${PCL_LIBRARIES})
