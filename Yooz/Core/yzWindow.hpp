#pragma once

#include <yzpch.hpp>

#include <Core/yzBase.hpp>
#include <Core/yzEvent.hpp>
#include <Math/yzVector2.hpp>

namespace yz
{
class Application;

class Window
{
public:
	EventQueue window_event;

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

	Application& GetApp() { return m_app; }

	Handle GetHandle() const;

	uint32_t GetID() const;

	uint32_t GetWidth() const;
	uint32_t GetHeight() const;
	Vec2u    GetSize() const;

	void SetSize(uint16_t w, uint16_t h);

	uint32_t GetPosX() const;
	uint32_t GetPosY() const;
	Vec2u    GetPosition() const;

	void SetPosition(uint16_t x, uint16_t);

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

	Application& m_app;
	Handle       m_handle;
	std::string  m_title;
	uint32_t     m_id;
};
}  // namespace yz
