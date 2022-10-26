#pragma once
#pragma once

#include <yzpch.hpp>

#include <Core/yzEvent.hpp>
#include <Input/yzInputCodes.hpp>
#include <Input/yzKeyboard.hpp>
#include <Input/yzMouse.hpp>
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

	void Update();

	Keyboard& GetKeyboard();
	Mouse&    GetMouse();


private:
	bool OnEvent(const EventArg& arg);

private:
	bool m_inited {false};

	Window& m_window;

	Keyboard m_keyboard;
	Mouse    m_mouse;
};
}  // namespace yz
