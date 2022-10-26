#include <Sandbox.hpp>


void Sandbox::OnInit()
{
	m_renderer.Init();
	m_input.Init();
}

void Sandbox::OnUpdate(float dt)
{
	m_input.Update();

	float speed = 500.0f;

	if(m_input.GetKeyboard().KeyDown(yz::Key::Left))
		pos.x -= speed * dt;
	if(m_input.GetKeyboard().KeyDown(yz::Key::Right))
		pos.x += speed * dt;
	if(m_input.GetKeyboard().KeyDown(yz::Key::Up))
		pos.y -= speed * dt;
	if(m_input.GetKeyboard().KeyDown(yz::Key::Down))
		pos.y += speed * dt;

	if(m_input.GetKeyboard().KeyReleased(yz::Key::Esc))
		Close();

	if(m_input.GetKeyboard().KeyPressed(yz::Key::F1))
		m_graphics_device.GetRasterizer().ToggleFillMode();

	if(m_input.GetKeyboard().KeyPressed(yz::Key::F11))
	{
		if(m_graphics_device.GetParams().GetFullscreenMode() ==
		   yz::FullscreenMode::Windowed)
			m_graphics_device.GetParams().SetFullscreenMode(
			        yz::FullscreenMode::Exclusive);
		else
			m_graphics_device.GetParams().SetFullscreenMode(
			        yz::FullscreenMode::Windowed);

		m_graphics_device.ApplyChanges();
	}

	if(m_input.GetKeyboard().KeyPressed(yz::Key::F9))
	{
		if(m_graphics_device.GetParams().GetVsyncMode() == yz::VsyncMode::Immediate)
			m_graphics_device.GetParams().SetVsyncMode(yz::VsyncMode::Synchronized);
		else
			m_graphics_device.GetParams().SetVsyncMode(yz::VsyncMode::Immediate);

		m_graphics_device.ApplyChanges();
	}
	YZ_INFO("dt: %f", dt);
}

void Sandbox::OnRender()
{
	m_renderer.Begin();

	m_renderer.DrawQuad(yz::Color::BLUE_VIOLET, pos, {32.0f, 32.0f}, 0.0f);

	m_renderer.DrawQuad(yz::Color::AZURE, {40.0f, 100.0f}, {128.0f, 128.0f}, 0.0f);

	m_renderer.DrawQuad(yz::Color::DEEP_PINK, pos + yz::Vec2 {128.0f},
	                    {128.0f, 128.0f}, 0.0f);
	m_renderer.End();
}

void Sandbox::OnExit()
{
	m_input.Shutdown();
	m_renderer.Destroy();
}
