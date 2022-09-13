#include <Core/yzApplication.hpp>
#include <Core/yzLogger.hpp>

namespace yz
{
Application::Application(const std::string& name, std::uint32_t width,
                         std::uint32_t height):
        m_name(name),
        m_bounds(0, 0, width, height), m_window(*this), m_graphics_device(*this)
{
}

void Application::Execute()
{
	Init();
	Update();
	Exit();
	YZ_INFO("Application Closed.");
}

void Application::Close()
{
	m_running = false;
	YZ_INFO("Closing Application.");
}
void Application::Kill() { std::exit(EXIT_SUCCESS); }

rectu Application::GetBounds() const { return m_bounds; }

const std::string Application::GetName() const { return m_name; }

GraphicsDevice Application::GetGraphicsDevice() const
{
	return m_graphics_device;
}

Window Application::GetWindow() const { return m_window; }


void Application::Init()
{
	if(m_inited) return;
	m_graphics_device.BeforeInit();

	m_window.Init();
	m_window.ClosingEvent.Add(this, &Application::Close);

	m_graphics_device.Init();
	m_graphics_device.SetColorBufferColor(Color::CYAN);



	m_inited = true;
}

void Application::Update()
{
	while(m_running)
	{
		m_window.Update();

		m_graphics_device.BeforeUpdate();
		m_graphics_device.Update();
	}
}

void Application::Exit()
{
	if(m_inited)
	{
		m_graphics_device.Destroy();
		m_window.Destroy();
	}
}

}  // namespace yz
