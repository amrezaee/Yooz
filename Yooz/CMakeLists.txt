#--------------------------------------------------------------------------------------------------
# FIND PACKAGES
#--------------------------------------------------------------------------------------------------
find_package(SDL2 REQUIRED QUIET)
find_package(ghc_filesystem REQUIRED QUIET)


#--------------------------------------------------------------------------------------------------
# SETUP YOOZ TARGET
#--------------------------------------------------------------------------------------------------
add_executable(Yooz)

#--------------------------------------------------------------------------------------------------
# OPENGL SPECIFIC
#--------------------------------------------------------------------------------------------------
if(YZ_GL_PLATFORM)
	include(yooz_gl_platform.cmake)
endif(YZ_GL_PLATFORM)


#--------------------------------------------------------------------------------------------------
# YOOZ CONFIGS
#--------------------------------------------------------------------------------------------------
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Yooz)

target_precompile_headers(Yooz PRIVATE "yzSTD.hpp" "yzDeps.hpp")

target_include_directories(Yooz PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/)

target_link_libraries(Yooz PRIVATE 
							SDL2::SDL2 SDL2::SDL2main SDL2::SDL2-static
							ghcFilesystem::ghc_filesystem)

set_target_properties(Yooz PROPERTIES WIN32_EXECUTABLE $<IF:$<CONFIG:Release>,TRUE,FALSE>)

target_compile_definitions(Yooz PRIVATE
	$<$<CONFIG:Debug>:YZ_DEBUG_BUILD>
	$<$<CONFIG:RelWithDebInfo>:YZ_PROFILE_BUILD>
	$<$<CONFIG:Release>:YZ_RELEASE_BUILD>
	
	$<$<BOOL:${YZ_GL_PLATFORM}>:YZ_GL_PLATFORM>
	$<$<BOOL:${YZ_VK_PLATFORM}>:YZ_VK_PLATFORM>
	$<$<BOOL:${YZ_PLATFORM_UNIX}>:YZ_PLATFORM_UNIX>
	$<$<BOOL:${YZ_PLATFORM_APPLE}>:YZ_PLATFORM_APPLE>
	$<$<BOOL:${YZ_PLATFORM_DESKTOP}>:YZ_PLATFORM_DESKTOP>
	$<$<BOOL:${YZ_PLATFORM_MOBILE}>:YZ_PLATFORM_MOBILE>
	$<$<BOOL:${YZ_PLATFORM_WINDOWS}>:YZ_PLATFORM_WINDOWS>
	$<$<BOOL:${YZ_PLATFORM_ANDROID}>:YZ_PLATFORM_ANDROID>
	$<$<BOOL:${YZ_PLATFORM_EMSCRIPTEN}>:YZ_PLATFORM_EMSCRIPTEN>
	$<$<BOOL:${YZ_PLATFORM_OSX}>:YZ_PLATFORM_OSX>
	$<$<BOOL:${YZ_PLATFORM_IOS}>:YZ_PLATFORM_IOS>
	$<$<BOOL:${YZ_PLATFORM_MSYS}>:YZ_PLATFORM_MSYS>
	$<$<BOOL:${YZ_PLATFORM_LINUX}>:YZ_PLATFORM_LINUX>

	$<$<BOOL:${YZ_COMPILER_MSVC}>:YZ_COMPILER_MSVC>
	$<$<BOOL:${YZ_COMPILER_GCC}>:YZ_COMPILER_GCC>
	$<$<BOOL:${YZ_COMPILER_CLANG}>:YZ_COMPILER_CLANG>
	$<$<BOOL:${YZ_COMPILER_INTEL}>:YZ_COMPILER_INTEL>
	$<$<BOOL:${YZ_COMPILER_EMSCRIPTEN}>:YZ_COMPILER_EMSCRIPTEN>)

if(YZ_COMPILER_MSVC)

	target_compile_options(Yooz PRIVATE /options:strict /permissive- /W4 /MP /GR- /nologo)

	target_compile_definitions(Yooz PRIVATE _ITERATOR_DEBUG_LEVEL=0 
											_HAS_EXCEPTIONS=0 
											_CRT_SECURE_NO_WARNINGS
											WIN32_LEAN_AND_MEAN
											NOMINMAX
											NOCOMM
											NOMENU
											NORASTEROPS
											NOGDI
	)

	if(CMAKE_CXX_FLAGS MATCHES "/EHsc ")
        string(REPLACE "/EHsc" "/EHs-c-" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    elseif(CMAKE_CXX_FLAGS MATCHES "/EHsc$")
        string(REPLACE "/EHsc" "/EHs-c-" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    endif()

else()
	target_compile_options(Yooz PRIVATE -Wall -Wextra -Wno-c++98-compat
										-Wno-c++98-compat-pedantic 
										-Wno-format-nonliteral -Wc++11-compat)
endif()
																	
#--------------------------------------------------------------------------------------------------
# COMMON SOURCES
#--------------------------------------------------------------------------------------------------
target_sources(Yooz PRIVATE
	"Core/yzApplication.cpp"
	"Core/yzAssert.cpp"
	"Core/yzEntryPoint.cpp"
	"Core/yzLogger.cpp"

	"Graphics/yzCamera.cpp"
	"Graphics/yzColor.cpp"
	"Graphics/yzGraphicsParams.cpp"

	"Math/yzFunctions.cpp"
	"Math/yzTransform.cpp"

	"Platform/SDL/yzMessageBox.SDL.cpp"
	"Platform/SDL/yzPlatform.SDL.cpp"
	"Platform/SDL/yzWindow.SDL.cpp")
