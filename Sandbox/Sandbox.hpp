#pragma once

#include <Yooz.hpp>

#include <memory>

class Sandbox final: public yz::Application
{
public:
	Sandbox(yz::AppSpecs& specs)
	        : yz::Application(specs), m_renderer(m_graphics_device)
	{
	}

	void OnInit() override;
	void OnUpdate(float dt) override;
	void OnRender() override;
	void OnExit() override;

private:
	yz::Renderer     m_renderer;
	yz::InputManager m_input {m_window};

	yz::Vec2 pos;
};

std::unique_ptr<yz::Application> yz::CreateApp()
{
	yz::AppSpecs s {"Sandbox"};
	return xtd::make_unique<Sandbox>(s);
}
