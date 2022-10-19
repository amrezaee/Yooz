#include <Core/yzApplication.hpp>

#include <Core/yzAssert.hpp>
#include <Core/yzLogger.hpp>
#include <Core/yzTimer.hpp>
#include <Math/yzTransform.hpp>

namespace yz
{
Application::Application(AppSpecs& specs): m_specs(specs), m_window(*this)
{
}

void Application::Run()
{
	Timer timer;

	Init();

	OnInit();

	while(m_running)
	{
		timer.Stop();
		m_delta_time = timer.Elapsed();
		timer.Reset();

		m_window.Update();

		if(!m_suspended)
		{
			OnUpdate(m_delta_time);
			OnRender(m_delta_time);

			m_graphics_device.SwapBuffers();
		}
	}

	Destroy();
}

void Application::Init()
{
	YZ_ASSERT(!m_inited);

	std::error_code code;

	if(!m_specs.working_dir.empty())
	{
		fs::current_path(m_specs.working_dir, code);
		// YZ_ERROR(code, code.message().c_str());
	}

	m_platform.Init();

	m_window.CloseEvent.Add(this, &Application::OnWindowClose);
	m_window.ActiveEvent.Add(this, &Application::OnWindowActive);
	m_window.DeactiveEvent.Add(this, &Application::OnWindowDeactive);
	m_window.ResizeEvent.Add(this, &Application::OnWindowResize);

	m_graphics_device.Init(m_specs.graphics_params, m_window);

	m_inited = true;
}

void Application::Destroy()
{
	YZ_ASSERT(m_inited);

	m_graphics_device.Destroy();

	m_window.CloseEvent.Remove(this, &Application::OnWindowClose);
	m_window.ActiveEvent.Remove(this, &Application::OnWindowActive);
	m_window.DeactiveEvent.Remove(this, &Application::OnWindowDeactive);
	m_window.ResizeEvent.Remove(this, &Application::OnWindowResize);

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

void Application::OnWindowActive()
{
	m_suspended = false;
}

void Application::OnWindowDeactive()
{
	m_suspended = true;
}

void Application::OnWindowClose()
{
	m_running = false;
}

void Application::OnWindowResize(Vec2u size)
{
	m_graphics_device.UpdateViewport(size);
	OnResize(size.x, size.y);
}
}  // namespace yz
