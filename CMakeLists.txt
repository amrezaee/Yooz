cmake_minimum_required(VERSION 3.20)

# prevent in-tree build
if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
    message(FATAL_ERROR "in-tree build is prevented.")
endif()

set(VCPKG_MANIFEST_FEATURES "yooz")
set(VCPKG_INSTALL_OPTIONS "--no-print-usage")

#--------------------------------------------------------------------------------------------------
# OPTIONS
#--------------------------------------------------------------------------------------------------
option(YZ_STATIC_CRT  "Use static CRT. (msvc only)" OFF)
option(YZ_BUILD_TESTS "Build tests"                 OFF)

if(YZ_BUILD_TEST)
	list(APPEND VCPKG_MANIFEST_FEATURES "tests")
endif()

#--------------------------------------------------------------------------------------------------
# PROJECT INFO AND SETUP
#--------------------------------------------------------------------------------------------------
project(Yooz2D DESCRIPTION "Yooz2D is a 2D game engine"
			   LANGUAGES   CXX C)
				   
if(NOT (CMAKE_SIZEOF_VOID_P EQUAL 8))
    message(FATAL_ERROR "Yooz2D only supports 64-bit CPUs.")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD          11  CACHE STRING "C++ standard to be used")
set(CMAKE_CXX_STANDARD_REQUIRED ON  CACHE BOOL   "Force C++ standard required")
set(CMAKE_CXX_EXTENSIONS        OFF CACHE BOOL   "C++ compiler extensions turn off")

set(CMAKE_C_STANDARD          11  CACHE STRING "C standard to be used")
set(CMAKE_C_STANDARD_REQUIRED ON  CACHE BOOL   "Force C standard required")
set(CMAKE_C_EXTENSIONS        OFF CACHE BOOL   "C compiler extensions")

if(MSVC AND YZ_STATIC_CRT)
	if(NOT (VCPKG_TARGET_TRIPLET MATCHES "windows-yooz-mt$"))
		message(FATAL_ERROR "Incompatible triplet used.")
	endif()
	
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>" CACHE STRING "MSVC runtime library type")
endif()

#--------------------------------------------------------------------------------------------------
# PLATFORM INFO
#--------------------------------------------------------------------------------------------------
if(UNIX)
	set(YZ_PLATFORM_UNIX TRUE CACHE BOOL "UNIX platform")
endif(UNIX)

if(APPLE)
	set(YZ_PLATFORM_APPLE TRUE CACHE BOOL "Apple platform")
endif(APPLE)

if((CMAKE_SYSTEM_NAME STREQUAL "Windows") OR WIN32)
	set(YZ_PLATFORM_WINDOWS TRUE CACHE BOOL "Windows platform")

elseif((CMAKE_SYSTEM_NAME STREQUAL "Android") OR ANDROID)
	set(YZ_PLATFORM_ANDROID TRUE CACHE BOOL "Android platform")

elseif((CMAKE_SYSTEM_NAME STREQUAL "Emscripten") OR EMSCRIPTEN)
	set(YZ_PLATFORM_EMSCRIPTEN TRUE CACHE BOOL "Emscripten platform")

elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	set(YZ_PLATFORM_OSX TRUE CACHE BOOL "MacOSX platform")

elseif(CMAKE_SYSTEM_NAME STREQUAL "iOS")
	set(YZ_PLATFORM_IOS TRUE CACHE BOOL "IOS platform")

elseif(CMAKE_SYSTEM_NAME STREQUAL "MSYS")
	set(YZ_PLATFORM_MSYS TRUE CACHE BOOL "MSYS platform")

elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	set(YZ_PLATFORM_LINUX TRUE CACHE BOOL "Linux platform")

else()
	message(FATAL_ERROR "Unsupported platform.")
endif()

if(YZ_PLATFORM_WINDOWS OR YZ_PLATFORM_LINUX OR YZ_PLATFORM_MYSYS OR YZ_PLATFORM_ANDROID OR YZ_PLATFORM_EMSCRIPTEN)
	set(YZ_GL_PLATFORM TRUE CACHE BOOL "OpenGL supported platforms")
	set(YZ_VK_PLATFORM TRUE CACHE BOOL "Vulkan supported platforms")
endif()

if(YZ_PLATFORM_WINDOWS OR YZ_PLATFORM_OSX OR YZ_PLATFORM_LINUX OR YZ_PLATFORM_MYSYS)
	set(YZ_PLATFORM_DESKTOP TRUE CACHE BOOL "Desktop platforms")
else()
	set(YZ_PLATFORM_MOBILE TRUE CACHE BOOL "Mobile platforms")
endif()

#--------------------------------------------------------------------------------------------------
# COMPILER INFO
#--------------------------------------------------------------------------------------------------
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set(YZ_COMPILER_MSVC TRUE CACHE BOOL "MSVC compiler")

elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(YZ_COMPILER_GCC TRUE CACHE BOOL "GNU compiler")

elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(YZ_COMPILER_CLANG TRUE CACHE BOOL "Clang compiler")

elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
	set(YZ_COMPILER_INTEL TRUE CACHE BOOL "Intel compiler")

elseif(YZ_PLATFORM_EMSCRIPTEN)
	set(YZ_COMPILER_EMSCRIPTEN TRUE CACHE BOOL "Emscripten compiler")

else()
	message(FATAL_ERROR "Unsupported compiler.")
endif()

#--------------------------------------------------------------------------------------------------
# SUBDIRECTORIES
#--------------------------------------------------------------------------------------------------
add_subdirectory(Yooz)

if(YZ_BUILD_TESTS)
	add_subdirectory(Tests)
endif()
