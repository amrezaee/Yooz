#include <Core/yzApplication.hpp>

#include <Core/yzAssert.hpp>
#include <Core/yzLogger.hpp>



namespace yz
{
Application::Application(AppSpecs& specs): m_specs(specs), m_window(*this)
{
}

void Application::Run()
{
	constexpr unsigned int delta_times_size = 4;
	float                  delta_times[delta_times_size] {};
	std::size_t            dti = 0;

	std::uint64_t current_time = m_platform.GetTime();
	std::uint64_t last_time    = 0;

	Init();

	OnInit();

	while(m_running)
	{
		last_time    = current_time;
		current_time = m_platform.GetTime();

		delta_times[dti & (delta_times_size - 1)] =
		        static_cast<float>(current_time - last_time) * 0.000001f;
		dti++;
		m_delta_time =
		        std::accumulate(delta_times, delta_times + delta_times_size, 0.0f) /
		        delta_times_size;

		m_window.Update();

		if(!m_suspended)
		{
			OnUpdate(m_delta_time);
			OnRender();

			m_graphics_device.SwapBuffers();
		}
	}

	Destroy();
}

void Application::OnRedraw()
{
	OnRender();
	m_graphics_device.SwapBuffers();
}

void Application::Close()
{
	m_running = false;
}

void Application::Kill()
{
	std::exit(EXIT_SUCCESS);
}

void Application::Init()
{
	YZ_ASSERT(!m_inited);

	std::error_code code;

	if(!m_specs.working_dir.empty())
	{
		fs::current_path(m_specs.working_dir, code);
		YZ_ASSERT(code, code.message().c_str());
	}

	m_platform.Init();

	m_window.window_event.AddHandler(this, &Application::OnEvent);

	m_graphics_device.Init(m_specs.graphics_params, m_window);

	m_inited = true;
}

void Application::Destroy()
{
	YZ_ASSERT(m_inited);

	m_graphics_device.Destroy();

	m_window.window_event.RemoveHandler(this, &Application::OnEvent);

	m_window.Destroy();

	m_platform.Shutdown();

	m_inited = false;
}

const AppSpecs& Application::GetSpecs() const
{
	return m_specs;
}

Platform& Application::GetPlatform()
{
	return m_platform;
}

Window& Application::GetWindow()
{
	return m_window;
}

GraphicsDevice& Application::GetGraphicsDevice()
{
	return m_graphics_device;
}

bool Application::IsActive() const
{
	return !m_suspended;
}

bool Application::IsCursorVisible() const
{
	return m_show_cursor;
}

void Application::ShowCursor(bool show)
{
	SDL_ShowCursor(show ? SDL_ENABLE : SDL_DISABLE);
}

bool Application::OnEvent(const EventArg& arg)
{
	switch(arg.type)
	{
	case EventType::Quit:
	{
		m_running = false;
		return true;
	}

	case EventType::Resize:
	{
		m_graphics_device.UpdateViewport({arg.u16[0], arg.u16[1]});
		OnResize(arg.u16[0], arg.u16[1]);
		return false;
	}

	case EventType::Focus:
	{
		m_suspended = !arg.u8[0];
		return true;
	}

	default: YZ_WARN("unknown event."); return false;
	}
}
}  // namespace yz
