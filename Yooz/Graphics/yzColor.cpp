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

bool Color::operator==(const Color rhs) const
{
	return GetRed() == rhs.GetRed() && GetGreen() == rhs.GetGreen() &&
	       GetBlue() == rhs.GetBlue() && GetAlpha() == rhs.GetAlpha();
}

}  // namespace yz
