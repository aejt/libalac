# CMakeList.txt : CMake project for libalac-example, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (alac_c_example src/main.cpp)

target_link_libraries(alac_c_example
    PUBLIC 
        alac_c
    PRIVATE
        
)