#pragma once

#include <Yooz.hpp>

#include <memory>

class Sandbox final: public yz::Application
{
public:
	Sandbox(yz::AppSpecs& specs)
	        : yz::Application(specs), m_renderer(m_graphics_device),
	          m_input(m_window)
	{
	}

	void OnInit() override;
	void OnUpdate(float dt) override;
	void OnRender(float dt) override;
	void OnResize(unsigned int w, unsigned int h) override;

private:
	yz::Renderer     m_renderer;
	yz::InputManager m_input;

	yz::Vec2 pos;
};

std::unique_ptr<yz::Application> yz::CreateApp()
{
	yz::AppSpecs s {"Sandbox"};
	return xtd::make_unique<Sandbox>(s);
}
