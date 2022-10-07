// Precompiled header for external dependencies
#pragma once

#ifdef YZ_GL_PLATFORM
	#define GLAD_GL_IMPLEMENTATION
	#include <glad/gl.h>
#endif

#include <ghc/filesystem.hpp>
namespace fs = ghc::filesystem;

#include <SDL.h>

