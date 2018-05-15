# CMakeList.txt : CMake project for libalac-example, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (libalac_example src/main.cpp)

target_link_libraries(libalac_example
    PUBLIC 
        libalac_c
    PRIVATE
        
)