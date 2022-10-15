#pragma once

#include <Input/yzInputCodes.hpp>
#include <Math/yzVector2.hpp>

#include <yzSTD.hpp>

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
	void OnKey(std::bitset<static_cast<std::size_t>(Key::Count)>& down,
	           std::bitset<static_cast<std::size_t>(Key::Count)>& press);

	void OnMouseButton(
	        std::bitset<static_cast<std::size_t>(MouseButton::Count)>& down,
	        std::bitset<static_cast<std::size_t>(MouseButton::Count)>& press);

	void OnMouseMotion(Vec2 pos);
	void OnMouseWheel(Vec2 state);

private:
	bool m_inited {false};

	Window& m_window;

	Vec2 m_mouse_pos;
	Vec2 m_mouse_wheel;

	std::bitset<static_cast<std::size_t>(Key::Count)> m_key_press_states;
	std::bitset<static_cast<std::size_t>(Key::Count)> m_key_down_states;

	std::bitset<static_cast<std::size_t>(MouseButton::Count)> m_mouse_press_states;
	std::bitset<static_cast<std::size_t>(MouseButton::Count)> m_mouse_down_states;
};
}  // namespace yz
