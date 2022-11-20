#include <Core/yzWindow.hpp>

#include <yzpch.hpp>

#include <Core/yzApplication.hpp>
#include <Core/yzAssert.hpp>
#include <Core/yzLogger.hpp>
#include <Input/yzInputCodes.hpp>

namespace yz
{
static int resize_watch(void* userdata, SDL_Event* event)
{
	Window* wp = reinterpret_cast<Window*>(userdata);

	switch(event->type)
	{
	case SDL_WINDOWEVENT:
	{
		switch(event->window.event)
		{
		case SDL_WINDOWEVENT_RESIZED:
		case SDL_WINDOWEVENT_SIZE_CHANGED:
		{
			EventArg earg;
			earg.type   = EventType::Resize;
			earg.u16[0] = static_cast<uint16_t>(event->window.data1);
			earg.u16[1] = static_cast<uint16_t>(event->window.data2);
			wp->window_event.Push(earg);
			wp->window_event.Raise();
		}
		break;


		case SDL_WINDOWEVENT_EXPOSED:
		{
			wp->GetApp().OnRedraw();
		}
		break;
		}
	}
	break;
	}

	return 0;
}

Window::Window(Application& app): m_app(app), m_handle {nullptr}, m_id(0)
{
}

void Window::Init(bool resizable, bool borderless)
{
	YZ_ASSERT(!m_inited);

	YZ_SINFO("Window Creation.");

	m_title         = m_app.GetSpecs().name;
	uint32_t width  = m_app.GetGraphicsDevice().GetParams().GetBufferWidth();
	uint32_t height = m_app.GetGraphicsDevice().GetParams().GetBufferHeight();

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

	SDL_AddEventWatch(resize_watch, this);

	SDL_SetWindowMinimumSize(sdlwin, 200, 200);

	YZ_INFO("Width:  %u", width);
	YZ_INFO("Height: %u", height);

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
	EventArg earg {};

	SDL_Event    e {0};
	SDL_Scancode sc {SDL_SCANCODE_UNKNOWN};

	while(SDL_PollEvent(&e))
	{
		switch(e.type)
		{
		case SDL_QUIT:
		{
			earg.type = EventType::Quit;
			window_event.Push(earg);
		}
		break;

		case SDL_KEYDOWN:
		{
			SDL_Keysym ks = e.key.keysym;

			sc = ks.scancode;

			if(m_allow_alt_f4)
			{
				if(((ks.mod & KMOD_LALT) || (ks.mod & KMOD_RALT)) &&
				   ks.scancode == SDL_SCANCODE_F4)
				{
					e.type = SDL_QUIT;
					SDL_PushEvent(&e);
				}
			}
		}
		break;

			/*case SDL_MOUSEWHEEL:
			{
			    earg.type   = EventType::MouseWheel;
			    earg.f32[0] = e.wheel.preciseX;
			    earg.f32[1] = e.wheel.preciseY;
			    mouse_event.Push(earg);
			}
			break;*/

		case SDL_WINDOWEVENT:
			if(e.window.windowID != m_id)
				break;

			switch(e.window.event)
			{
			case SDL_WINDOWEVENT_FOCUS_GAINED:
			{
				m_active   = true;
				earg.type  = EventType::Focus;
				earg.u8[0] = m_active;
				window_event.Push(earg);
			}
			break;

			case SDL_WINDOWEVENT_FOCUS_LOST:
			{
				m_active   = false;
				earg.type  = EventType::Focus;
				earg.u8[0] = m_active;
				window_event.Push(earg);
			}
			break;

			case SDL_WINDOWEVENT_CLOSE:
				e.type = SDL_QUIT;
				SDL_PushEvent(&e);
				break;
			}
		}
	}

	window_event.Raise();
}

Handle Window::GetHandle() const
{
	return m_handle;
}

uint32_t Window::GetID() const
{
	return m_id;
}

uint32_t Window::GetWidth() const
{
	return GetSize().x;
}

uint32_t Window::GetHeight() const
{
	return GetSize().y;
}

Vec2u Window::GetSize() const
{
	int w, h;
	SDL_GetWindowSize(static_cast<SDL_Window*>(m_handle), &w, &h);
	return {w, h};
}

void Window::SetSize(uint16_t w, uint16_t h)
{
	SDL_SetWindowSize(static_cast<SDL_Window*>(m_handle), static_cast<int>(w),
	                  static_cast<int>(h));

	EventArg a {};
	a.type   = EventType::Resize;
	a.u16[0] = w;
	a.u16[1] = h;
	window_event.Push(a);
	window_event.Raise();
}

uint32_t Window::GetPosX() const
{
	return GetPosition().x;
}

uint32_t Window::GetPosY() const
{
	return GetPosition().y;
}

Vec2u Window::GetPosition() const
{
	int x, y;
	SDL_GetWindowPosition(static_cast<SDL_Window*>(m_handle), &x, &y);
	return {x, y};
}

void Window::SetPosition(uint16_t x, uint16_t y)
{
	SDL_SetWindowPosition(static_cast<SDL_Window*>(m_handle), x, y);
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
