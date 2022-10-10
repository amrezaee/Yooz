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

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(MSVC AND YZ_STATIC_CRT)
	if(NOT (VCPKG_TARGET_TRIPLET MATCHES "windows-yooz-mt$"))
		message(FATAL_ERROR "Incompatible triplet used.")
	endif()
	
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

#--------------------------------------------------------------------------------------------------
# PLATFORM INFO
#--------------------------------------------------------------------------------------------------
if(UNIX)
	set(YZ_PLATFORM_UNIX TRUE)
endif(UNIX)

if(APPLE)
	set(YZ_PLATFORM_APPLE TRUE)
endif(APPLE)

if((CMAKE_SYSTEM_NAME MATCHES     "Windows")    OR WIN32)
	set(YZ_PLATFORM_WINDOWS    TRUE)

elseif((CMAKE_SYSTEM_NAME MATCHES "Android")    OR ANDROID)
	set(YZ_PLATFORM_ANDROID    TRUE)

elseif((CMAKE_SYSTEM_NAME MATCHES "Emscripten") OR EMSCRIPTEN)
	set(YZ_PLATFORM_EMSCRIPTEN TRUE)

elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
	set(YZ_PLATFORM_OSX        TRUE)

elseif(CMAKE_SYSTEM_NAME MATCHES "iOS")
	set(YZ_PLATFORM_IOS        TRUE)

elseif(CMAKE_SYSTEM_NAME MATCHES "MSYS")
	set(YZ_PLATFORM_MSYS      TRUE)

elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(YZ_PLATFORM_LINUX      TRUE)

else()
	message(FATAL_ERROR "Unsupported platform.")
endif()

if(YZ_PLATFORM_WINDOWS OR YZ_PLATFORM_LINUX OR YZ_PLATFORM_MYSYS OR YZ_PLATFORM_ANDROID OR YZ_PLATFORM_EMSCRIPTEN)
	set(YZ_GL_PLATFORM TRUE)
	set(YZ_VK_PLATFORM TRUE)
endif()

if(YZ_PLATFORM_WINDOWS OR YZ_PLATFORM_OSX OR YZ_PLATFORM_LINUX OR YZ_PLATFORM_MYSYS)
	set(YZ_PLATFORM_DESKTOP TRUE)
else()
	set(YZ_PLATFORM_MOBILE TRUE)
endif()

#--------------------------------------------------------------------------------------------------
# COMPILER INFO
#--------------------------------------------------------------------------------------------------
if(CMAKE_CXX_COMPILER_ID MATCHES     "MSVC")
	set(YZ_COMPILER_MSVC TRUE)

elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	set(YZ_COMPILER_GCC TRUE)

elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	set(YZ_COMPILER_CLANG TRUE)

elseif(CMAKE_CXX_COMPILER_ID MATCHES "Intel")
	set(YZ_COMPILER_INTEL TRUE)

elseif(YZ_PLATFORM_EMSCRIPTEN)
	set(YZ_COMPILER_EMSCRIPTEN TRUE)

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
