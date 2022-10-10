#pragma once

#include <Core/yzBase.hpp>
#include <Core/yzEvent.hpp>
#include <Math/yzVector2.hpp>

#include <yzSTD.hpp>

namespace yz
{
class Application;

class Window
{
public:
	Event<Vec2u> ResizeEvent;
	Event<Vec2u> MoveEvent;
	Event<>      CloseEvent;
	Event<>      ActiveEvent;
	Event<>      DeactiveEvent;

public:
	Window(Application& app);

	Window(const Window&)            = delete;
	Window& operator=(const Window&) = delete;

	Window(Window&&)            = delete;
	Window& operator=(Window&&) = delete;

	void Init(bool resizable = true, bool borderless = false);
	void Reinit(bool resizable = true, bool borderless = false);
	void Destroy();

	void Update();

	Handle GetHandle() const;

	std::uint32_t GetID() const;

	std::uint32_t GetWidth() const;
	std::uint32_t GetHeight() const;
	Vec2u         GetSize() const;

	void SetSize(Vec2u size);

	std::uint32_t GetPosX() const;
	std::uint32_t GetPosY() const;
	Vec2u         GetPosition() const;

	void SetPosition(Vec2u pos);

	const std::string& GetTitle() const;
	void               SetTitle(const std::string& title);

	bool IsActive() const;

	bool IsResizable() const;
	void SetResizable(bool resizable);

	bool IsBorderless() const;
	void SetBorderless(bool borderless);

	bool IsAltF4Enabled() const;
	void EnableAltF4(bool enable);

private:
	bool m_inited {false};
	bool m_active {true};
	bool m_resizable {true};
	bool m_borderless {false};
	bool m_allow_alt_f4 {false};

	Handle        m_handle;
	Application&  m_app;
	std::string   m_title;
	std::uint32_t m_id;
};
}  // namespace yz
