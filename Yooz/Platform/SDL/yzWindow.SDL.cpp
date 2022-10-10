#include <Core/yzWindow.hpp>

#include <Core/yzApplication.hpp>
#include <Core/yzAssert.hpp>
#include <Core/yzLogger.hpp>

#include <yzDeps.hpp>

namespace yz
{
Window::Window(Application& app): m_app(app), m_handle {nullptr}, m_id(0)
{
}

void Window::Init(bool resizable, bool borderless)
{
	YZ_ASSERT(!m_inited);

	YZ_INFO("Creating window...");

	m_title              = m_app.GetSpecs().name;
	std::uint32_t width  = m_app.GetGraphicsDevice().GetParams().GetBufferWidth();
	std::uint32_t height = m_app.GetGraphicsDevice().GetParams().GetBufferHeight();

	m_resizable  = resizable;
	m_borderless = borderless;

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
	                            SDL_WINDOWPOS_CENTERED, width, height, flags);
	YZ_ASSERT(m_handle, SDL_GetError());

	SDL_Window* sdlwin = static_cast<SDL_Window*>(m_handle);

	m_id = SDL_GetWindowID(sdlwin);

	if(m_app.IsCursorVisible())
		SDL_ShowCursor(SDL_ENABLE);
	else
		SDL_ShowCursor(SDL_DISABLE);

	ActiveEvent.Raise();

	YZ_INFO("Window created.");

	m_inited = true;
}

void Window::Reinit(bool resizable, bool borderless)
{
	Destroy();
	Init(resizable, borderless);
}

void Window::Destroy()
{
	YZ_ASSERT(m_inited);

	SDL_DestroyWindow(static_cast<SDL_Window*>(m_handle));
	m_handle = nullptr;

	m_inited = false;
}

void Window::Update()
{
	SDL_Event   e {0};
	SDL_Keycode key {0}, lastkey {0};

	while(SDL_PollEvent(&e))
	{
		switch(e.type)
		{
		case SDL_QUIT: CloseEvent.Raise(); break;

		case SDL_KEYDOWN:
		{
			// this does not work
			// is this a bug in SDL?
			if(m_allow_alt_f4)
			{
				lastkey = key;
				key     = e.key.keysym.sym;
				if((lastkey == SDLK_LALT || lastkey == SDLK_RALT) && key == SDLK_F4)
				{
					e.type = SDL_QUIT;
					SDL_PushEvent(&e);
				}
			}
		}
		break;

		case SDL_KEYUP:
		{
			// nothing here
		}
		break;

		case SDL_WINDOWEVENT:
			if(e.window.windowID != m_id)
				break;

			switch(e.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				ResizeEvent.Raise(Vec2u {e.window.data1, e.window.data2});
				break;

			case SDL_WINDOWEVENT_MOVED:
				MoveEvent.Raise(Vec2u {e.window.data1, e.window.data2});
				break;

			case SDL_WINDOWEVENT_FOCUS_GAINED:
				m_active = true;
				ActiveEvent.Raise();
				break;

			case SDL_WINDOWEVENT_FOCUS_LOST:
				m_active = false;
				DeactiveEvent.Raise();
				break;

			case SDL_WINDOWEVENT_CLOSE:
				e.type = SDL_QUIT;
				SDL_PushEvent(&e);
				break;
			}
		}
	}
}

Handle Window::GetHandle() const
{
	return m_handle;
}

std::uint32_t Window::GetID() const
{
	return m_id;
}

std::uint32_t Window::GetWidth() const
{
	return GetSize().x;
}

std::uint32_t Window::GetHeight() const
{
	return GetSize().y;
}

Vec2u Window::GetSize() const
{
	int w, h;
	SDL_GetWindowSize(static_cast<SDL_Window*>(m_handle), &w, &h);
	return {w, h};
}

void Window::SetSize(Vec2u size)
{
	SDL_SetWindowSize(static_cast<SDL_Window*>(m_handle), size.x, size.y);
	ResizeEvent.Raise(size);
}

std::uint32_t Window::GetPosX() const
{
	return GetPosition().x;
}

std::uint32_t Window::GetPosY() const
{
	return GetPosition().y;
}

Vec2u Window::GetPosition() const
{
	int x, y;
	SDL_GetWindowPosition(static_cast<SDL_Window*>(m_handle), &x, &y);
	return {x, y};
}

void Window::SetPosition(Vec2u pos)
{
	SDL_SetWindowPosition(static_cast<SDL_Window*>(m_handle), pos.x, pos.y);
	MoveEvent.Raise(pos);
}

const std::string& Window::GetTitle() const
{
	return m_title;
}

void Window::SetTitle(const std::string& title)
{
	SDL_SetWindowTitle(static_cast<SDL_Window*>(m_handle), title.c_str());
	m_title = title;
}

bool Window::IsActive() const
{
	return m_active;
}

bool Window::IsResizable() const
{
	return m_resizable;
}

void Window::SetResizable(bool resizable)
{
	if(m_resizable == resizable)
		return;
	SDL_SetWindowResizable(static_cast<SDL_Window*>(m_handle),
	                       resizable ? SDL_TRUE : SDL_FALSE);
	m_resizable = resizable;
}

bool Window::IsBorderless() const
{
	return m_borderless;
}

void Window::SetBorderless(bool borderless)
{
	if(m_borderless == borderless)
		return;
	SDL_SetWindowBordered(static_cast<SDL_Window*>(m_handle),
	                      borderless ? SDL_FALSE : SDL_TRUE);
	m_borderless = borderless;
}

bool Window::IsAltF4Enabled() const
{
	return m_allow_alt_f4;
}

void Window::EnableAltF4(bool enable)
{
	m_allow_alt_f4 = enable;
}
}  // namespace yz
