#pragma once
#pragma once

#include <yzpch.hpp>

#include <Core/yzEvent.hpp>
#include <Input/yzInputCodes.hpp>
#include <Math/yzVector2.hpp>

namespace yz
{
class Window;

class InputManager
{
public:
	InputManager(Window& window);

	void Init();
	void Shutdown();

	bool KeyPressed(Key key) const;
	bool KeyReleased(Key key) const;
	bool KeyDown(Key key) const;

	bool MousePressed(MouseButton button) const;
	bool MouseReleased(MouseButton button) const;
	bool MouseDown(MouseButton button) const;

	Vec2 MousePos() const;
	Vec2 MouseWheel() const;

private:
	bool OnEvent(const EventArg& arg);

private:
	bool m_inited {false};

	Window& m_window;

	Vec2 m_mouse_pos;
	Vec2 m_mouse_wheel;

	std::bitset<static_cast<std::size_t>(Key::Count)> m_key_current_states;
	std::bitset<static_cast<std::size_t>(Key::Count)> m_key_last_states;

	std::bitset<static_cast<std::size_t>(MouseButton::Count)> m_mouse_current_states;
	std::bitset<static_cast<std::size_t>(MouseButton::Count)> m_mouse_last_states;
};
}  // namespace yz
