# CMakeList.txt : CMake project for libalac-c, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_library (libalac_c src/ALACEncoder.cpp src/ALACDecoder.cpp)

target_link_libraries(libalac_c
    PUBLIC 
        libalac
    PRIVATE   
		
)

target_include_directories(libalac_c
    INTERFACE 
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/include/libalac-c
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)