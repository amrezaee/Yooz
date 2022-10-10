#include <Core/yzApplication.hpp>

#include <Core/yzLogger.hpp>
#include <Core/yzTimer.hpp>
#include <Graphics/yzCamera.hpp>
#include <Graphics/yzShader.hpp>
#include <Math/yzTransform.hpp>

namespace yz
{
Application::Application(AppSpecs& specs)
        : m_specs(specs), m_window(*this), m_renderer(m_graphics_device)
{
}

void Application::Run()
{
	Init();

	Timer timer;
	float delta_time {0.0f};

	m_graphics_device.SetClearColor(Color::YELLOW);

	while(m_running)
	{
		// TODO: may be convert Color class to abgr?
		// Game loop timing
		timer.Stop();
		delta_time = timer.Elapsed();
		timer.Reset();

		if(!m_suspended)
		{
			// TODO: begin whitout camera sets camera to wrong position
			m_renderer.Begin();

			Vec2 pos(0.0f, -270.0f);
			for(unsigned int i = 0; i < 200; ++i)
			{
				pos.x = -480.0f;
				for(unsigned int j = 0; j < 200; ++j)
				{
					m_renderer.DrawQuad(Color::BLACK, pos, {4}, 0.0f);
					pos.x += 5;
				}
				pos.y += 5;
			}
			float s = (float)SDL_GetTicks64() * 0.004f;
			m_renderer.DrawQuad(Color::AZURE, {0, 0},
			                    {128.0f * std::sin(s), 128.0f * std::sin(s)},
			                    (float)SDL_GetTicks64() * 0.05f);

			m_renderer.End();

			/*YZ_TRACE("Draw Calls: %d  Quads: %d", m_renderer.GetStats().draw_calls,
			         m_renderer.GetStats().quads);*/

			m_graphics_device.SwapBuffers();
		}

		m_window.Update();
	}

	Destroy();
}

void Application::Init()
{
	YZ_ASSERT(!m_inited);

	m_platform.Init();

	m_window.CloseEvent.Add(this, &Application::OnWindowClose);
	m_window.ActiveEvent.Add(this, &Application::OnWindowActive);
	m_window.DeactiveEvent.Add(this, &Application::OnWindowDeactive);
	m_window.ResizeEvent.Add(this, &Application::OnWindowResize);

	m_graphics_device.Init(m_specs.graphics_params, m_window);

	m_renderer.Init();

	m_inited = true;
}

void Application::Destroy()
{
	YZ_ASSERT(m_inited);

	m_renderer.Destroy();

	m_graphics_device.Destroy();

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

	m_renderer.OnResize(size);
}
}  // namespace yz
