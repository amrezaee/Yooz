#include <Graphics/yzGraphicsDevice.hpp>

#include <Core/yzApplication.hpp>
#include <Core/yzAssert.hpp>
#include <Core/yzLogger.hpp>

#include <yzDeps.hpp>

namespace yz
{
#ifdef YZ_DEBUG_BUILD
void GLDebugOutput(GLenum, GLenum, GLuint, GLenum, GLsizei, const char*,
                   const void*);
#endif  // YZ_DEBUG_BUILD

GraphicsDevice::GraphicsDevice(): m_api(GraphicsAPI::GL)
{
}

void GraphicsDevice::SetupParams()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
	                    SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

#ifdef YZ_DEBUG_BUILD
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	// SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);
	// SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	if(m_params.GetMSAALevel() != MSAALevel::None)
	{
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,
		                    static_cast<int>(m_params.GetMSAALevel()));
	}
}

bool GraphicsDevice::CheckParams()
{
	int v;

	SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &v);
	YZ_ASSERT(v == SDL_GL_CONTEXT_PROFILE_CORE,
	          "OpenGL core profile is not available.");

	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &v);
	YZ_ASSERT(v >= 4, "OpenGL 4.5+ required.");

	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &v);
	YZ_ASSERT(v >= 5, "OpenGL 4.5+ required.");

	// SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &v);
	//  YZ_ASSERT(v == 1, "Double buffered OpenGL context required.");

	SDL_GL_GetAttribute(SDL_GL_ACCELERATED_VISUAL, &v);
	YZ_ASSERT(v == 1, "GPU is not available.");

	if(m_params.GetMSAALevel() != MSAALevel::None)
	{
		SDL_GL_GetAttribute(SDL_GL_MULTISAMPLESAMPLES, &v);
		if(v != static_cast<int>(m_params.GetMSAALevel()))
		{
			m_params.SetMSAALevel(static_cast<MSAALevel>(v));
			return false;
		}
	}

	return true;
}

void GraphicsDevice::Init(GraphicsParams& params, Window& window)
{
	YZ_ASSERT(!m_inited);

	YZ_INFO("Initializing graphics device...");

	m_params = params;

	SetupParams();
	window.Init();
	CheckParams();

	m_params.SetWindowHandle(window.GetHandle());

	SDL_Window* sdlwin = static_cast<SDL_Window*>(window.GetHandle());

	m_handle = SDL_GL_CreateContext(sdlwin);
	YZ_ASSERT(m_handle, SDL_GetError());

	int code = SDL_GL_MakeCurrent(sdlwin, static_cast<SDL_GLContext>(m_handle));
	YZ_ASSERT(code == 0, SDL_GetError());

	code = gladLoadGL(reinterpret_cast<GLADloadfunc>(SDL_GL_GetProcAddress));
	YZ_ASSERT(code, "Cannot Load OpenGL.");

#ifdef YZ_DEBUG_BUILD
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(&yz::GLDebugOutput, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr,
	                      GL_TRUE);
#endif  // YZ_DEBUG_BUILD

	m_features.Init();

	YZ_INFO("\tVendor:       %s", glGetString(GL_VENDOR));
	YZ_INFO("\tRenderer:     %s", glGetString(GL_RENDERER));
	YZ_INFO("\tProfile:      Core");
	YZ_INFO("\tVersion:      %s", glGetString(GL_VERSION));
	YZ_INFO("\tGLSL Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));

	YZ_INFO("\tDriver:       %s", m_features.GetDriverName());

	YZ_INFO("\tTotal texture units: %i", m_features.TotalTextureUnits());
	YZ_INFO("\tTotal texture units available in fragment shader: %i",
	        m_features.FragmentShaderTextureUnits());

	YZ_INFO("\tDXT1:         %s",
	        m_features.HasDXT1() ? "Supported" : "Not supported");

	YZ_INFO("\tS3TC:         %s",
	        m_features.HasS3TC() ? "Supported" : "Not supported");

	YZ_INFO("\tPVRTC:        %s",
	        m_features.HasPVRTC() ? "Supported" : "Not supported");

	YZ_INFO("\tETC1:         %s",
	        m_features.HasETC1() ? "Supported" : "Not supported");

	YZ_INFO("\tETC2:         %s",
	        m_features.HasETC2() ? "Supported" : "Not supported");

	YZ_INFO("\tATITC:        %s",
	        m_features.HasATITC() ? "Supported" : "Not supported");

	YZ_INFO("Graphics device created.");

	m_inited = true;
}

void GraphicsDevice::Destroy()
{
	YZ_ASSERT(m_inited);

	SDL_GL_DeleteContext(static_cast<SDL_GLContext>(m_handle));

	m_inited = false;
}

void GraphicsDevice::SetClearColor(Color color)
{
	float t[4];
	m_clear_color = color;
	m_clear_color.GetColors(t);
	glClearColor(t[0], t[1], t[2], t[3]);
}

void GraphicsDevice::ClearBuffers() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicsDevice::SwapBuffers() const
{
	SDL_GL_SwapWindow(static_cast<SDL_Window*>(m_params.GetWindowHandle()));
}

void GraphicsDevice::UpdateViewport(Vec2u size)
{
	m_params.SetBufferSize(size);
	glViewport(0, 0, size.x, size.y);
}

Handle GraphicsDevice::GetHandle() const
{
	return m_handle;
}

GraphicsAPI GraphicsDevice::GetAPI() const
{
	return m_api;
}

GraphicsParams& GraphicsDevice::GetParams()
{
	return m_params;
}

const GraphicsFeatures& GraphicsDevice::GetFeatures() const
{
	return m_features;
}

#ifdef YZ_DEBUG_BUILD
void GLDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity,
                   GLsizei length, const char* message, const void* userparam)
{
	YZ_UNUSED(userparam);
	YZ_UNUSED(length);
	YZ_UNUSED(severity);
	YZ_UNUSED(id);

	const char *src, *tp;
	switch(source)
	{
	case GL_DEBUG_SOURCE_API: src = "API"; break;
	case GL_DEBUG_SOURCE_OTHER: src = "Other Sources"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY: src = "Third Party Software"; break;
	case GL_DEBUG_SOURCE_APPLICATION: src = "Application"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM: src = "Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: src = "Shader Compiler"; break;
	default: src = "Unknown"; break;
	}

	switch(type)
	{
	case GL_DEBUG_TYPE_ERROR: tp = "Error"; break;
	case GL_DEBUG_TYPE_OTHER: tp = "Other Type"; break;
	case GL_DEBUG_TYPE_MARKER: tp = "Marker"; break;
	case GL_DEBUG_TYPE_POP_GROUP: tp = "Pop Group"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP: tp = "Push Group"; break;
	case GL_DEBUG_TYPE_PORTABILITY: tp = "Portability Issue"; break;
	case GL_DEBUG_TYPE_PERFORMANCE: tp = "Performance Issue"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: tp = "Undefined Behavior"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: tp = "Deprecated Behavior"; break;
	default: tp = "Unknown"; break;
	}

	if(type == GL_DEBUG_TYPE_ERROR || type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR)
	{
		YZ_ERROR("OpenGL %s in %s: %s", tp, src, message);
		YZ_ASSERT(0);
	}
	else
		YZ_WARN("OpenGL %s in %s: %s", tp, src, message);
}
#endif  // YZ_DEBUG_BUILD
}  // namespace yz
