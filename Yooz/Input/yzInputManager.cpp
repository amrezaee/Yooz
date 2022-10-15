#include <Input/yzInputManager.hpp>

#include <Core/yzAssert.hpp>
#include <Core/yzWindow.hpp>


namespace yz
{
InputManager::InputManager(Window& window): m_window(window)
{
}

void InputManager::Init()
{
	YZ_ASSERT(!m_inited);

	m_window.KeyEvent.Add(this, &InputManager::OnKey);
	m_window.MouseButtonEvent.Add(this, &InputManager::OnMouseButton);
	m_window.MouseMotionEvent.Add(this, &InputManager::OnMouseMotion);
	m_window.MouseWheelEvent.Add(this, &InputManager::OnMouseWheel);

	m_inited = true;
}

void InputManager::Shutdown()
{
	YZ_ASSERT(m_inited);

	m_window.KeyEvent.Remove(this, &InputManager::OnKey);
	m_window.MouseButtonEvent.Remove(this, &InputManager::OnMouseButton);
	m_window.MouseMotionEvent.Remove(this, &InputManager::OnMouseMotion);
	m_window.MouseWheelEvent.Remove(this, &InputManager::OnMouseWheel);

	m_inited = false;
}

bool InputManager::KeyPressed(Key key) const
{
	int k = static_cast<int>(key);
	return m_key_press_states[k];
}

bool InputManager::KeyReleased(Key key) const
{
	int k = static_cast<int>(key);
	return !m_key_press_states[k];
}

bool InputManager::KeyDown(Key key) const
{
	int k = static_cast<int>(key);
	return m_key_down_states[k];
}

bool InputManager::MousePressed(MouseButton button) const
{
	int b = static_cast<int>(button);
	return m_mouse_press_states[b];
}

bool InputManager::MouseReleased(MouseButton button) const
{
	int b = static_cast<int>(button);
	return !m_mouse_press_states[b];
}

bool InputManager::MouseDown(MouseButton button) const
{
	int b = static_cast<int>(button);
	return m_mouse_down_states[b];
}

Vec2 InputManager::MousePos() const
{
	return m_mouse_pos;
}

Vec2 InputManager::MouseWheel() const
{
	return m_mouse_wheel;
}

void InputManager::OnKey(std::bitset<static_cast<std::size_t>(Key::Count)>& down,
                         std::bitset<static_cast<std::size_t>(Key::Count)>& press)
{
	m_key_down_states  = down;
	m_key_press_states = press;
}

void InputManager::OnMouseButton(
        std::bitset<static_cast<std::size_t>(MouseButton::Count)>& down,
        std::bitset<static_cast<std::size_t>(MouseButton::Count)>& press)
{
	m_mouse_down_states  = down;
	m_mouse_press_states = press;
}

void InputManager::OnMouseMotion(Vec2 pos)
{
	m_mouse_pos = pos;
}

void InputManager::OnMouseWheel(Vec2 state)
{
	m_mouse_wheel = state;
}
}  // namespace yz
