# CMakeList.txt : CMake project for libalac-c, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_library (alac_c src/ALACEncoder.cpp src/ALACDecoder.cpp)

target_link_libraries(alac_c
    PUBLIC 
        alac
    PRIVATE   
		
)

target_include_directories(alac_c
    INTERFACE 
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/include/libalac-c
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

install(TARGETS alac_c DESTINATION bin)