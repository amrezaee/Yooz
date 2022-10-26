#include <Input/yzMouse.hpp>

namespace yz
{
void Mouse::Update()
{
	m_last_button_states = m_button_states;
	int x, y;
	m_button_states = SDL_GetMouseState(&x, &y);

	m_pos.x = static_cast<float>(x);
	m_pos.y = static_cast<float>(y);
}

bool Mouse::Clicked(MouseButton btn)
{
	if((m_button_states & SDL_BUTTON(static_cast<int>(btn))) &&
	   !(m_last_button_states & SDL_BUTTON(static_cast<int>(btn))))
		return true;
	return false;
}

bool Mouse::DoubleClicked(MouseButton btn)
{
	bool clk    = Clicked(btn);
	bool result = false;

	if(clk && (m_click_timer.ElapsedMilli() <= m_double_click_time))
		result = true;
	else if(clk && (m_click_timer.ElapsedMilli() > m_double_click_time))
		m_click_timer.Reset();

	return result;
}

bool Mouse::IsDown(MouseButton btn)
{
	return m_button_states & SDL_BUTTON(static_cast<int>(btn));
}

bool Mouse::Released(MouseButton btn)
{
	return (m_last_button_states & SDL_BUTTON(static_cast<int>(btn))) &&
	       !(m_button_states & SDL_BUTTON(static_cast<int>(btn)));
}

Vec2 Mouse::GetPos() const
{
	return m_pos;
}
Vec2 Mouse::GetWheel() const
{
	return m_wheel;
}


void Mouse::SetDoubleClickTime(float time)
{
	m_double_click_time = time;
}
}  // namespace yz
