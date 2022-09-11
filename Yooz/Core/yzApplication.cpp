#include <Core/yzApplication.hpp>

namespace yz
{
Application::Application(const std::string& name, std::uint32_t width,
                         std::uint32_t height):
        m_name(name),
        m_bounds(0, 0, width, height)
{
}
void Application::Execute()
{
	Init();
	Update();
	Exit();
}

void Application::Close() { m_running = false; }
void Application::Kill() { std::exit(EXIT_SUCCESS); }

rectu Application::GetBounds() const { return m_bounds; }

const std::string Application::GetName() const { return m_name; }

void Application::Init()
{
	if(m_inited) return;

	m_window.Init(*this);
	m_window.ExitingEvent.Add(this, &Application::Close);




	m_inited = true;
}

void Application::Update()
{
	while(m_running) { m_window.Update(); }
}

void Application::Exit() { m_window.Destroy(); }

}  // namespace yz
