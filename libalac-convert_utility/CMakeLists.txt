# CMakeList.txt : CMake project for libalac-convert-utility, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (libalac-convert-utility src/main.cpp src/CAFFileALAC.cpp)

# OS Specifics
if (WIN32)
	target_compile_definitions(libalac-convert-utility PRIVATE TARGET_OS_WIN32)
endif (WIN32)

target_link_libraries(libalac-convert-utility libalac)

target_include_directories(libalac-convert-utility
    PUBLIC 
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)