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

GraphicsDevice::GraphicsDevice(Application& app):
        m_api(GraphicsAPI::GL), m_app(app)
{
}

void GraphicsDevice::BeforeInit()
{
	if(m_inited) return;

	int code = SDL_InitSubSystem(SDL_INIT_VIDEO);
	YZ_ASSERT(code == 0, SDL_GetError());

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
	                    SDL_GL_CONTEXT_PROFILE_CORE);

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
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);
}

void GraphicsDevice::Init()
{
	if(m_inited) return;

	m_handle = SDL_GL_CreateContext(
	        static_cast<SDL_Window*>(m_app.GetWindow().GetHandle()));
	YZ_ASSERT(m_handle, SDL_GetError());

	int code = SDL_GL_MakeCurrent(
	        static_cast<SDL_Window*>(m_app.GetWindow().GetHandle()),
	        static_cast<SDL_GLContext>(m_handle));
	YZ_ASSERT(code == 0, SDL_GetError());

	code = gladLoadGLLoader(SDL_GL_GetProcAddress);
	YZ_ASSERT(code, "Cannot Load OpenGL.");

#ifdef YZ_DEBUG_BUILD
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(&yz::GLDebugOutput, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr,
	                      GL_TRUE);
#endif  // YZ_DEBUG_BUILD

	YZ_INFO("OpenGL Context Created.");
	YZ_INFO("\tVendor:        %s", glGetString(GL_VENDOR));
	YZ_INFO("\tRenderer:      %s", glGetString(GL_RENDERER));
	YZ_INFO("\tVersion:       %s", glGetString(GL_VERSION));
	YZ_INFO("\tGLSL Version:  %s", glGetString(GL_SHADING_LANGUAGE_VERSION));

	m_inited = true;
}

void GraphicsDevice::BeforeUpdate()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicsDevice::Update()
{
	SDL_GL_SwapWindow(static_cast<SDL_Window*>(m_app.GetWindow().GetHandle()));
}

void GraphicsDevice::Destroy()
{
	if(m_inited)
	{
		SDL_GL_DeleteContext(static_cast<SDL_GLContext>(m_handle));
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
	}
	m_inited = false;
}

void GraphicsDevice::SetColorBufferColor(Color color)
{
	m_color_buffer_color = color;
	glClearColor(m_color_buffer_color.GetRed(), m_color_buffer_color.GetGreen(),
	             m_color_buffer_color.GetBlue(),
	             m_color_buffer_color.GetAlpha());
}

GraphicsAPI GraphicsDevice::GetAPI() const { return m_api; }

Handle GraphicsDevice::GetHandle() const { return m_handle; }

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
		YZ_ERROR("OpenGL %s in %s: %s", tp, src, message);
	else
		YZ_WARN("OpenGL %s in %s: %s", tp, src, message);
}
#endif  // YZ_DEBUG_BUILD

}  // namespace yz
