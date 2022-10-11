#include <Graphics/yzColor.hpp>


namespace yz
{
const Color Color::WHITE {0xffffffff};
const Color Color::TRANS_WHITE {0xffffff00};
const Color Color::BLACK {};
const Color Color::RED {0xff0000ff};
const Color Color::GREEN {0x00ff00ff};
const Color Color::BLUE {0x0000ffff};
const Color Color::YELLOW {0xffff00ff};
const Color Color::CYAN {0x00ffffff};
const Color Color::MAGENTA {0xff00ffff};
const Color Color::BROWN {0x964B00ff};
const Color Color::PURPLE {0xa020f0ff};

const Color Color::ALICE_BLUE {0xf0f8ffff};
const Color Color::ANTIQUE_WHITE {0xfaebd7ff};
const Color Color::AQUA {0x00ffffff};
const Color Color::AQUAMARINE {0x7fffd4ff};
const Color Color::AZURE {0x007fffff};
const Color Color::BLUE_VIOLET {0x8a2be2ff};
const Color Color::BURLYWOOD {0xdeb887ff};
const Color Color::CADET_BLUE {0x5f9ea0ff};
const Color Color::CHARTREUSE {0xdfff00ff};
const Color Color::CHOCOLATE {0x7b3f00ff};
const Color Color::CORNFLOWER_BLUE {0x6495edff};
const Color Color::CORNSILK {0xfff8dcff};
const Color Color::CRIMSON {0xdc143cff};
const Color Color::DARK_ORCHID {0x9932ccff};
const Color Color::DARK_SALAMON {0xe9967aff};
const Color Color::DEEP_PINK {0xaa336aff};
const Color Color::FLORAL_WHITE {0xfffaf0ff};
const Color Color::GHOST_WHITE {0xf8f8ffff};
const Color Color::GOLD {0xffd700ff};
const Color Color::INDIGO {0x4b0082ff};
const Color Color::IVORY {0xfffff0ff};
const Color Color::LAVENDER {0xe6e6faff};
const Color Color::LAWN_GREEN {0x7cfc00ff};
const Color Color::LIGHT_CORAL {0xf08080ff};
const Color Color::MOCCASIN {0xffe4b5ff};
const Color Color::PLUM {0x673147ff};
const Color Color::POWDER_BLUE {0xb6d0e2ff};
const Color Color::ROYAL_BLUE {0x4169e1ff};
const Color Color::ROSY_BROWN {0xbc8f8fff};
const Color Color::SLATE_BLUE {0x6a5acdff};
const Color Color::SNOW {0xfffafaff};
const Color Color::TEAL {0x008080ff};
const Color Color::TURQUOISE {0x30d5c8ff};
const Color Color::WHITE_SMOKE {0xf5f5f5ff};
const Color Color::YELLOW_GREEN {0x9acd32ff};

void Color::Set(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
{
	m_value = static_cast<std::uint32_t>(r << 24u) |
	          static_cast<std::uint32_t>(g << 16u) |
	          static_cast<std::uint32_t>(b << 8u) | static_cast<std::uint32_t>(a);
}

void Color::Set(float r, float g, float b, float a)
{
	m_value = static_cast<std::uint8_t>(r * 255u) |
	          static_cast<std::uint8_t>(g * 255u) |
	          static_cast<std::uint8_t>(b * 255u) |
	          static_cast<std::uint8_t>(a * 255u);
}

void Color::Set(std::uint8_t r, std::uint8_t g, std::uint8_t b)
{
	Set(r, g, b, 255u);
}

void Color::Set(float r, float g, float b)
{
	Set(r, g, b, 1.0f);
}


void Color::SetRed(std::uint8_t r)
{
	m_value = static_cast<std::uint32_t>(m_value & 0x00ffffff) |
	          static_cast<std::uint32_t>(r << 24u);
}

void Color::SetGreen(std::uint8_t g)
{
	m_value = static_cast<std::uint32_t>(m_value & 0xff00ffff) |
	          static_cast<std::uint32_t>(g << 16u);
}

void Color::SetBlue(std::uint8_t b)
{
	m_value = static_cast<std::uint32_t>(m_value & 0xffff00ff) |
	          static_cast<std::uint32_t>(b << 8u);
}

void Color::SetAlpha(std::uint8_t a)
{
	m_value = (m_value & 0xffffff00) | a;
}

void Color::SetRed(float r)
{
	SetRed(static_cast<std::uint8_t>(r * 255));
}

void Color::SetGreen(float g)
{
	SetGreen(static_cast<std::uint8_t>(g * 255));
}

void Color::SetBlue(float b)
{
	SetBlue(static_cast<std::uint8_t>(b * 255));
}

void Color::SetAlpha(float a)
{
	SetAlpha(static_cast<std::uint8_t>(a * 255));
}

void Color::SetPacked(std::uint32_t pack)
{
	m_value = pack;
}

void Color::GetColors(float* const out) const
{
	out[0] = static_cast<float>(GetRed()) / 255.0f;
	out[1] = static_cast<float>(GetGreen()) / 255.0f;
	out[2] = static_cast<float>(GetBlue()) / 255.0f;
	out[3] = static_cast<float>(GetAlpha()) / 255.0f;
}

bool Color::operator==(Color rhs) const
{
	return GetRed() == rhs.GetRed() && GetGreen() == rhs.GetGreen() &&
	       GetBlue() == rhs.GetBlue() && GetAlpha() == rhs.GetAlpha();
}

}  // namespace yz
