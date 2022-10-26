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


	m_inited = true;
}

void InputManager::Shutdown()
{
	YZ_ASSERT(m_inited);

	m_inited = false;
}

void InputManager::Update()
{
	m_mouse.Update();
}

Keyboard& InputManager::GetKeyboard()
{
	return m_keyboard;
}

Mouse& InputManager::GetMouse()
{
	return m_mouse;
}
}  // namespace yz
