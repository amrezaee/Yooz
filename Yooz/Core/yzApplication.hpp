#pragma once

#include <Core/yzWindow.hpp>
#include <Graphics/yzGraphicsDevice.hpp>
#include <Graphics/yzGraphicsParams.hpp>
#include <Math/yzRectangle.hpp>
#include <Platform/yzPlatform.hpp>

#include <yzStds.hpp>

namespace yz
{
class Application
{
public:
	Application(const std::string& name, std::uint32_t width,
	            std::uint32_t height);

	void Execute();
	void Close();
	void Kill();

	Rectu GetBounds() const;

	const std::string GetName() const;

	GraphicsDevice GetGraphicsDevice() const;

	Window GetWindow() const;

	bool IsCursorVisible() const;
	void ShowCursor(bool show);

private:
	void Init();
	void Update();
	void Exit();

private:
	bool           m_inited {false};
	bool           m_show_cursor {true};
	bool           m_running {true};
	bool           m_suspended {false};
	Platform       m_platform;
	std::string    m_name;
	Window         m_window;
	GraphicsDevice m_graphics_device;
	GraphicsParams m_graphics_params;
	Rectu          m_bounds;
};
}  // namespace yz
