#pragma once

#include <yzpch.hpp>

#include <Core/yzWindow.hpp>
#include <Graphics/yzGraphicsDevice.hpp>
#include <Graphics/yzGraphicsParams.hpp>
#include <Platform/yzPlatform.hpp>

namespace yz
{
struct AppSpecs
{
	std::string    name;
	fs::path       working_dir;
	GraphicsParams graphics_params;
};

class Application
{
public:
	Application(AppSpecs& specs);

	virtual void OnInit()           = 0;
	virtual void OnUpdate(float dt) = 0;
	virtual void OnRender()         = 0;
	virtual void OnExit()           = 0;

	virtual void OnResize(std::uint16_t, std::uint16_t) {};
	virtual void OnRedraw();

	void Close();
	void Kill();

	const AppSpecs& GetSpecs() const;

	Platform& GetPlatform();

	Window& GetWindow();

	GraphicsDevice& GetGraphicsDevice();

	bool IsActive() const;

	bool IsCursorVisible() const;
	void ShowCursor(bool show);

private:
	void Run();
	void Init();
	void Destroy();
	friend int ::main(int argc, char** argv);

private:
	bool OnEvent(const EventArg& arg);

private:
	bool m_inited {false};
	bool m_running {true};
	bool m_suspended {false};
	bool m_show_cursor {true};

	float m_delta_time {0.0f};

protected:
	AppSpecs       m_specs;
	Platform       m_platform;
	Window         m_window;
	GraphicsDevice m_graphics_device;
};

std::unique_ptr<Application> CreateApp();
}  // namespace yz
