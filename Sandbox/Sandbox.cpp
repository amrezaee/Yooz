#include <Sandbox.hpp>


void Sandbox::OnInit()
{
	m_renderer.Init();
	m_input.Init();
}

void Sandbox::OnUpdate(float dt)
{
	float speed = 400.0f;

	if(m_input.KeyDown(yz::Key::Left))
		pos.x -= speed * dt;
	else if(m_input.KeyDown(yz::Key::Right))
		pos.x += speed * dt;
	else if(m_input.KeyDown(yz::Key::Up))
		pos.y -= speed * dt;
	else if(m_input.KeyDown(yz::Key::Down))
		pos.y += speed * dt;
}

void Sandbox::OnRender(float dt)
{
	m_renderer.Begin();
	m_renderer.DrawQuad(yz::Color::AZURE, pos, {128.0f, 128.0f}, 0.0f);
	m_renderer.End();
}

void Sandbox::OnResize(unsigned int w, unsigned int h)
{
}
