#pragma once

#include <Core/yzBase.hpp>
#include <Core/yzEvent.hpp>
#include <Math/yzRectangle.hpp>
#include <Math/yzVector2.hpp>

#include <yzStds.hpp>

namespace yz
{
class Application;

class Window
{
public:
	Event<>                             ClosingEvent;
	Event<std::uint32_t, std::uint32_t> ResizedEvent;
	Event<std::uint32_t, std::uint32_t> MovedEvent;

public:
	Window(Application& app);

	void Init();
	void Destroy();

	void Update();

	Handle GetHandle() const;

	std::string GetTitle() const;
	void        SetTitle(const std::string& title);

	bool IsActive() const;

	void SetBorders(bool show);
	void SetResizable(bool enable);

	vec2u GetPosition() const;

private:
	void Resized(std::uint32_t width, std::uint32_t height);
	void Moved(std::uint32_t x, std::uint32_t y);

private:
	Application&  m_app;
	std::string   m_title;
	rectu         m_bounds;
	bool          m_inited {false};
	bool          m_resizable {true};
	bool          m_borderless {false};
	bool          m_is_active {true};
	Handle        m_handle {nullptr};
	std::uint32_t m_id {0};
};
}  // namespace yz
