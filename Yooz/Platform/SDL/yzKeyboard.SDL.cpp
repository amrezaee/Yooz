#include <Input/yzKeyboard.hpp>

namespace yz
{
Keyboard::Keyboard()
{
	m_down_states = SDL_GetKeyboardState(nullptr);
}

bool Keyboard::HasScreenKeyboard()
{
	return SDL_HasScreenKeyboardSupport() == SDL_TRUE;
}
bool Keyboard::IsScreenKeyboardShown(const Window& window)
{
	return SDL_IsScreenKeyboardShown(static_cast<SDL_Window*>(window.GetHandle())) ==
	       SDL_TRUE;
}

bool Keyboard::KeyDown(Key key)
{
	return m_down_states[static_cast<int>(key)];
}

bool Keyboard::KeyPressed(Key key)
{
	bool r = false;
	int  k = static_cast<int>(key);

	if(static_cast<bool>(m_down_states[k]) != m_press_states[k])
	{
		if(m_press_states[k])
			r = false;
		else
			r = true;
		m_press_states[k].flip();
	}
	return r;
}

bool Keyboard::KeyReleased(Key key)
{
	bool r = false;
	int  k = static_cast<int>(key);
	if(static_cast<bool>(m_down_states[k]) != m_press_states[k])
	{
		if(m_press_states[k])
			r = true;
		else
			r = false;
		m_press_states[k].flip();
	}
	return r;
}
}  // namespace yz
