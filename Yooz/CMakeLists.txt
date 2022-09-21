find_package(SDL2 REQUIRED)
find_package(glad REQUIRED)

add_executable(Yooz)

target_link_libraries(Yooz PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2-static glad::glad)

set_target_properties(Yooz PROPERTIES	MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL"
										WIN32_EXECUTABLE     $<IF:$<CONFIG:Release>,TRUE,FALSE>)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Yooz)

target_include_directories(Yooz PRIVATE "/")

target_compile_definitions(Yooz PRIVATE

	$<$<CONFIG:Debug>:YZ_DEBUG_BUILD>
	$<$<CONFIG:Release>:YZ_RELEASE_BUILD>
	
    $<$<CXX_COMPILER_ID:MSVC>:YZ_COMPILER_MSVC=1
							_HAS_EXCEPTIONS=0
							_CRT_SECURE_NO_WARNINGS 
							_CRT_NONSTDC_NO_DEPRECATE 
							_CRT_SECURE_NO_DEPRECATE>
	$<$<CXX_COMPILER_ID:GNU>:YZ_COMPILER_GCC>
	$<$<CXX_COMPILER_ID:Clang>:YZ_COMPILER_CLANG>
	
	$<$<PLATFORM_ID:Windows>:YZ_PLATFORM_WINDOWS>
	$<$<PLATFORM_ID:Linux>:YZ_PLATFORM_LINUX>)
 
target_compile_options(Yooz PRIVATE

    $<$<CXX_COMPILER_ID:MSVC>:/W4 /MP>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>: -Wall -Wextra -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-format-nonliteral -Wc++11-compat>)
	
if(MSVC)
	if(CMAKE_CXX_FLAGS MATCHES "/EHsc ")
        string(REPLACE "/EHsc" "/EHs-c-" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    elseif(CMAKE_CXX_FLAGS MATCHES "/EHsc$")
        string(REPLACE "/EHsc" "/EHs-c-" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    endif()
endif()
																	
target_precompile_headers(Yooz PRIVATE "yzStds.hpp" "yzDeps.hpp")


target_sources(Yooz PRIVATE
	"Core/yzApplication.cpp"
	"Core/yzAssert.cpp"
	"Core/yzEntryPoint.cpp"
	"Core/yzLogger.cpp"

	"Graphics/yzCamera.cpp"
	"Graphics/yzColor.cpp"

	"Math/yzFunctions.cpp"
	"Math/yzTransform.cpp"

	"Platform/GL/yzGraphicsDevice.GL.cpp"
	"Platform/GL/yzGraphicsFeatures.GL.cpp"
	"Platform/GL/yzShader.GL.cpp"

	"Platform/SDL/yzMessageBox.SDL.cpp"
	"Platform/SDL/yzPlatform.SDL.cpp"
	"Platform/SDL/yzWindow.SDL.cpp")
