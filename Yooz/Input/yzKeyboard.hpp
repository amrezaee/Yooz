#pragma once

#include <yzpch.hpp>

#include <Core/yzWindow.hpp>
#include <Input/yzInputCodes.hpp>

namespace yz
{
class Keyboard
{
public:
	Keyboard();

	bool HasScreenKeyboard();
	bool IsScreenKeyboardShown(const Window& window);

	bool KeyDown(Key key);
	bool KeyPressed(Key key);
	bool KeyReleased(Key key);

private:
	const std::uint8_t*                               m_down_states {nullptr};
	std::bitset<static_cast<std::size_t>(Key::Count)> m_press_states;
};
}  // namespace yz
