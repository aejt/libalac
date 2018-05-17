# CMakeList.txt : CMake project for libalac-convert-utility, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (alac-convert-utility src/main.cpp src/CAFFileALAC.cpp)

# OS Specifics
if (WIN32)
	target_compile_definitions(alac-convert-utility PRIVATE TARGET_OS_WIN32)
endif (WIN32)

target_link_libraries(alac-convert-utility alac)

target_include_directories(alac-convert-utility
    PUBLIC 
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)