cmake_minimum_required(VERSION 3.20)

# prevent in-tree build
if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
    message(FATAL_ERROR "in-tree build is prevented. Please create a build directory.")
endif()

# first search for libs in default locations and then if they not found use vcpkg
#set(VCPKG_PREFER_SYSTEM_LIBS ON CACHE BOOL "")

project(YoozEngine DESCRIPTION "Yooz is a 2D game engine"
				   LANGUAGES   CXX C)
				   
if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(FATAL_ERROR "YoozEngine only supports 64-bit CPUs.")
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_subdirectory(Yooz)
