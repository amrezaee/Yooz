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

	m_window.mouse_event.AddHandler(this, &InputManager::OnEvent);
	m_window.keyboard_event.AddHandler(this, &InputManager::OnEvent);

	m_inited = true;
}

void InputManager::Shutdown()
{
	YZ_ASSERT(m_inited);

	m_window.mouse_event.RemoveHandler(this, &InputManager::OnEvent);
	m_window.keyboard_event.RemoveHandler(this, &InputManager::OnEvent);

	m_inited = false;
}

bool InputManager::KeyPressed(Key key) const
{
	int k = static_cast<int>(key);
	return m_key_current_states[k];
}

bool InputManager::KeyReleased(Key key) const
{
	int k = static_cast<int>(key);
	return !m_key_current_states[k];
}

bool InputManager::KeyDown(Key key) const
{
	int k = static_cast<int>(key);
	return m_key_current_states[k] && !m_key_last_states[k];
}

bool InputManager::MousePressed(MouseButton button) const
{
	int b = static_cast<int>(button);
	return m_mouse_current_states[b];
}

bool InputManager::MouseReleased(MouseButton button) const
{
	int b = static_cast<int>(button);
	return !m_mouse_current_states[b];
}

bool InputManager::MouseDown(MouseButton button) const
{
	int b = static_cast<int>(button);
	return m_mouse_current_states[b] && !m_mouse_last_states[b];
}

Vec2 InputManager::MousePos() const
{
	return m_mouse_pos;
}

Vec2 InputManager::MouseWheel() const
{
	return m_mouse_wheel;
}

bool InputManager::OnEvent(const EventArg& ea)
{
	switch(ea.type)
	{
	case EventType::KeyPress:
	{
		std::uint16_t i         = ea.u16[0];
		m_key_last_states[i]    = m_key_current_states[i];
		m_key_current_states[i] = 1;
		return true;
	}

	case EventType::KeyRelease:
	{
		std::uint16_t i         = ea.u16[0];
		m_key_last_states[i]    = m_key_current_states[i];
		m_key_current_states[i] = 0;
		return true;
	}

	case EventType::MousePress:
	{
		std::uint8_t i            = ea.u8[0];
		m_mouse_last_states[i]    = m_mouse_current_states[i];
		m_mouse_current_states[i] = 1;
		return true;
	}

	case EventType::MouseRelease:
	{
		std::uint8_t i            = ea.u8[0];
		m_mouse_last_states[i]    = m_mouse_current_states[i];
		m_mouse_current_states[i] = 0;
		return true;
	}

	case EventType::MouseMove:
	{
		m_mouse_pos.x = ea.f32[0];
		m_mouse_pos.y = ea.f32[1];
		return true;
	}

	case EventType::MouseWheel:
	{
		m_mouse_wheel.x = ea.f32[0];
		m_mouse_wheel.y = ea.f32[1];
		return true;
	}

	default: YZ_WARN("unknown event."); return false;
	}
}
}  // namespace yz
