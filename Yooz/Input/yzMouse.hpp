#pragma once

#include <yzpch.hpp>

#include <Core/yzTimer.hpp>
#include <Input/yzInputCodes.hpp>
#include <Math/yzVector2.hpp>

namespace yz
{
class Mouse
{
public:
	Mouse() = default;

	void Update();

	bool Clicked(MouseButton btn);
	bool DoubleClicked(MouseButton btn);
	bool IsDown(MouseButton btn);
	bool Released(MouseButton btn);

	Vec2 GetPos() const;
	Vec2 GetWheel() const;  // TODO: impl. this

	void SetDoubleClickTime(float time);

private:
	std::uint32_t m_button_states {0};
	std::uint32_t m_last_button_states {0};

	Vec2 m_pos;
	Vec2 m_wheel;

	Timer m_click_timer;
	float m_double_click_time {400.0f};  // in ms
};
}  // namespace yz
