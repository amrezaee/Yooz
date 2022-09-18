#include <Core/yzWindow.hpp>

#include <Core/yzApplication.hpp>
#include <Core/yzAssert.hpp>
#include <Core/yzLogger.hpp>

#include <yzDeps.hpp>

namespace yz
{
Window::Window(Application& app, std::uint32_t width, std::uint32_t height):
        m_app(app), m_bounds(rectu(0, 0, width, height))
{
}

void Window::Init()
{
	if(m_inited) return;

	m_title = m_app.GetName();
	YZ_INFO("Creating window {%s %dx%d}...", m_title, m_bounds.w, m_bounds.h);

	int flags = 0;
	flags |= (m_resizable ? SDL_WINDOW_RESIZABLE : 0);
	flags |= (m_borderless ? SDL_WINDOW_BORDERLESS : 0);
	flags |= (SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS);

	switch(m_app.GetGraphicsDevice().GetAPI())
	{
	case GraphicsAPI::GL:
	case GraphicsAPI::ES: flags |= SDL_WINDOW_OPENGL; break;
	case GraphicsAPI::VK: flags |= SDL_WINDOW_VULKAN; break;
	}

	m_handle = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED,
	                            SDL_WINDOWPOS_CENTERED, m_bounds.w, m_bounds.h,
	                            flags);
	YZ_ASSERT(m_handle, SDL_GetError());

	SDL_GetWindowPosition(static_cast<SDL_Window*>(m_handle),
	                      reinterpret_cast<int*>(&m_bounds.x),
	                      reinterpret_cast<int*>(&m_bounds.y));

	m_id = SDL_GetWindowID(static_cast<SDL_Window*>(m_handle));

	if(m_app.IsCursorVisible())
		SDL_ShowCursor(SDL_ENABLE);
	else
		SDL_ShowCursor(SDL_DISABLE);

	m_inited = true;
	YZ_INFO("Window created.");
}

void Window::Destroy()
{
	if(m_inited) { SDL_DestroyWindow(static_cast<SDL_Window*>(m_handle)); }
	m_inited = false;
}

void Window::Update()
{
	SDL_Event e {0};

	while(SDL_PollEvent(&e))
	{
		switch(e.type)
		{
		case SDL_QUIT: ClosingEvent.Raise(); break;

		case SDL_WINDOWEVENT:
			if(e.window.windowID != m_id) break;

			switch(e.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				Resized(static_cast<std::uint32_t>(e.window.data1),
				        static_cast<std::uint32_t>(e.window.data2));
				break;

			case SDL_WINDOWEVENT_MOVED:
				Moved(static_cast<std::uint32_t>(e.window.data1),
				      static_cast<std::uint32_t>(e.window.data2));
				break;

			case SDL_WINDOWEVENT_FOCUS_GAINED: m_is_active = true; break;

			case SDL_WINDOWEVENT_FOCUS_LOST: m_is_active = false; break;

			case SDL_WINDOWEVENT_CLOSE:
				e.type = SDL_QUIT;
				SDL_PushEvent(&e);
				break;
			}
		}
	}
}


Handle Window::GetHandle() const { return m_handle; }

std::string Window::GetTitle() const { return m_title; }

void Window::SetTitle(const std::string& title)
{
	m_title = title;
	SDL_SetWindowTitle(static_cast<SDL_Window*>(m_handle), m_title.c_str());
}

bool Window::IsActive() const { return m_is_active; }

void Window::SetBorders(bool show)
{
	if(show == m_borderless) return;
	m_borderless = show;
	SDL_SetWindowBordered(static_cast<SDL_Window*>(m_handle),
	                      m_borderless ? SDL_FALSE : SDL_TRUE);
}

void Window::SetResizable(bool enable)
{
	if(enable == m_resizable) return;
	m_resizable = enable;
	SDL_SetWindowResizable(static_cast<SDL_Window*>(m_handle),
	                       m_resizable ? SDL_TRUE : SDL_FALSE);
}

vec2u Window::GetPosition() const { return vec2u {m_bounds.x, m_bounds.y}; }


void Window::Resized(std::uint32_t width, std::uint32_t height)
{
	SDL_GetWindowSize(static_cast<SDL_Window*>(m_handle),
	                  reinterpret_cast<int*>(&m_bounds.w),
	                  reinterpret_cast<int*>(&m_bounds.h));

	MovedEvent.Raise(m_bounds.x, m_bounds.y);

	YZ_TRACE("Resized %dx%d", width, height);
}

void Window::Moved(std::uint32_t x, std::uint32_t y)
{
	SDL_GetWindowPosition(static_cast<SDL_Window*>(m_handle),
	                      reinterpret_cast<int*>(&m_bounds.x),
	                      reinterpret_cast<int*>(&m_bounds.y));

	MovedEvent.Raise(m_bounds.x, m_bounds.y);

	YZ_TRACE("Moved %dx%d", x, y);
}
}  // namespace yz
