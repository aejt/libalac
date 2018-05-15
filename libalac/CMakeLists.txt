# CMakeList.txt : CMake project for libalac, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(ALAC_C_SRC src/ag_dec.c src/ag_enc.c src/ALACBitUtilities.c src/dp_dec.c src/dp_enc.c src/EndianPortable.c src/matrix_dec.c src/matrix_enc.c)
set(ALAC_CPP_SRC src/ALACEncoder.cpp src/ALACDecoder.cpp)

# Compile C files as C++
set_source_files_properties(${ALAC_C_SRC} PROPERTIES LANGUAGE CXX )

add_library (libalac ${ALAC_CPP_SRC} ${ALAC_C_SRC})

if (WIN32)
	target_compile_definitions(libalac PRIVATE TARGET_OS_WIN32)
endif (WIN32)

target_include_directories(libalac 
    PUBLIC 
	INTERFACE
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>		
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/libalac
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)