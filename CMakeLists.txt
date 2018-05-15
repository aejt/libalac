# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("libalac")

# Include sub-projects.
add_subdirectory ("libalac")
add_subdirectory ("libalac-c")
add_subdirectory ("libalac-convert_utility")
add_subdirectory ("libalac-c-example")