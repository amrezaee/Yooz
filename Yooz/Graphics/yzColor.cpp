#include <Graphics/yzColor.hpp>


namespace yz
{
const Color Color::WHITE   = Color(0xffffffff);
const Color Color::BLACK   = Color();
const Color Color::RED     = Color(0xff0000ff);
const Color Color::GREEN   = Color(0x00ff00ff);
const Color Color::BLUE    = Color(0x0000ffff);
const Color Color::YELLOW  = Color(0xffff00ff);
const Color Color::CYAN    = Color(0x00ffffff);
const Color Color::MAGENTA = Color(0xff00ffff);

std::uint8_t Color::GetRed() const
{
	return static_cast<std::uint8_t>(m_value >> 24u);
}

std::uint8_t Color::GetGreen() const
{
	return static_cast<std::uint8_t>(m_value >> 16u);
}

std::uint8_t Color::GetBlue() const
{
	return static_cast<std::uint8_t>(m_value >> 8u);
}

std::uint8_t Color::GetAlpha() const
{
	return static_cast<std::uint8_t>(m_value);
}

void Color::SetRed(std::uint8_t r)
{
	m_value = std::uint32_t(m_value & 0x00ffffff) | std::uint32_t(r << 24u);
}

void Color::SetGreen(std::uint8_t g)
{
	m_value = std::uint32_t(m_value & 0xff00ffff) | std::uint32_t(g << 16u);
}

void Color::SetBlue(std::uint8_t b)
{
	m_value = std::uint32_t(m_value & 0xffff00ff) | std::uint32_t(b << 8u);
}

void Color::SetAlpha(std::uint8_t a) { m_value = (m_value & 0xffffff00) | a; }

bool Color::operator==(const Color rhs) const
{
	return GetRed() == rhs.GetRed() && GetGreen() == rhs.GetGreen() &&
	       GetBlue() == rhs.GetBlue() && GetAlpha() == rhs.GetAlpha();
}

}  // namespace yz
