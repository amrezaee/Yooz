#pragma once

#include <Core/yzBase.hpp>
#include <Core/yzEvent.hpp>
#include <Math/yzRectangle.hpp>

#include <yzStds.hpp>

namespace yz
{
class Application;

class Window
{
public:
	Event<> ExitingEvent;

public:
	void Init(const Application& app);
	void Destroy();

	void Update();

	handle GetHandle() const;

	std::string GetTitle() const;
	void        SetTitle(const std::string& title);

	bool IsActive() const;

	void SetBorders(bool show);
	void SetResizable(bool enable);

private:
	void Resized(std::uint32_t width, std::uint32_t height);
	void Moved(std::uint32_t x, std::uint32_t y);

private:
	std::string   m_title;
	rectu         m_bounds;
	bool          m_inited {false};
	bool          m_resizable {true};
	bool          m_borderless {false};
	bool          m_is_active {true};
	handle        m_handle {nullptr};
	std::uint32_t m_id {0};
};
}  // namespace yz
