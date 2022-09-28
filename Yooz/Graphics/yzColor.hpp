#pragma once

#include <yzStds.hpp>

namespace yz
{
// 32bit packed Color type in RGBA format
class Color
{
private:
	std::uint32_t m_value {0u};

public:
	constexpr Color()                        = default;
	constexpr Color(const Color&)            = default;
	constexpr Color(Color&&)                 = default;
	constexpr Color& operator=(const Color&) = default;
	constexpr Color& operator=(Color&&)      = default;

	constexpr Color(const std::uint32_t color): m_value(color) {}

	constexpr Color(const std::uint8_t r, const std::uint8_t g,
	                const std::uint8_t b, const std::uint8_t a):

	        m_value(static_cast<std::uint32_t>(r << 24u) |
	                static_cast<std::uint32_t>(g << 16u) |
	                static_cast<std::uint32_t>(b << 8u) |
	                static_cast<std::uint32_t>(a))
	{
	}

	constexpr Color(const float r, const float g, const float b, const float a):
	        Color(static_cast<std::uint8_t>(r * 255u),
	              static_cast<std::uint8_t>(g * 255u),
	              static_cast<std::uint8_t>(b * 255u),
	              static_cast<std::uint8_t>(a * 255u))
	{
	}

	constexpr Color(const std::uint8_t r, const std::uint8_t g,
	                const std::uint8_t b):
	        Color(r, g, b, 255u)
	{
	}

	constexpr Color(const float r, const float g, const float b):
	        Color(r, g, b, 1.0f)
	{
	}

	constexpr Color(const Color color, const std::uint8_t alpha):
	        m_value((color.m_value << 8) | alpha)
	{
	}

	constexpr Color(const Color color, const float alpha):
	        Color(color, static_cast<std::uint8_t>(alpha * 255u))
	{
	}

	constexpr void Set(const std::uint8_t r, const std::uint8_t g,
	                   const std::uint8_t b, const std::uint8_t a)
	{
		m_value = static_cast<std::uint32_t>(r << 24u) |
		          static_cast<std::uint32_t>(g << 16u) |
		          static_cast<std::uint32_t>(b << 8u) |
		          static_cast<std::uint32_t>(a);
	}

	constexpr void Set(const float r, const float g, const float b,
	                   const float a)
	{
		m_value = static_cast<std::uint8_t>(r * 255u) |
		          static_cast<std::uint8_t>(g * 255u) |
		          static_cast<std::uint8_t>(b * 255u) |
		          static_cast<std::uint8_t>(a * 255u);
	}

	constexpr void Set(const std::uint8_t r, const std::uint8_t g,
	                   const std::uint8_t b)
	{
		Set(r, g, b, 255u);
	}

	constexpr void Set(const float r, const float g, const float b)
	{
		Set(r, g, b, 1.0f);
	}

	constexpr std::uint8_t GetRed() const
	{
		return static_cast<std::uint8_t>(m_value >> 24u);
	}

	constexpr std::uint8_t GetGreen() const
	{
		return static_cast<std::uint8_t>(m_value >> 16u);
	}

	constexpr std::uint8_t GetBlue() const
	{
		return static_cast<std::uint8_t>(m_value >> 8u);
	}

	constexpr std::uint8_t GetAlpha() const
	{
		return static_cast<std::uint8_t>(m_value);
	}

	constexpr void SetRed(const std::uint8_t r)
	{
		m_value = static_cast<std::uint32_t>(m_value & 0x00ffffff) |
		          static_cast<std::uint32_t>(r << 24u);
	}

	constexpr void SetGreen(const std::uint8_t g)
	{
		m_value = static_cast<std::uint32_t>(m_value & 0xff00ffff) |
		          static_cast<std::uint32_t>(g << 16u);
	}

	constexpr void SetBlue(const std::uint8_t b)
	{
		m_value = static_cast<std::uint32_t>(m_value & 0xffff00ff) |
		          static_cast<std::uint32_t>(b << 8u);
	}

	constexpr void SetAlpha(const std::uint8_t a)
	{
		m_value = (m_value & 0xffffff00) | a;
	}

	constexpr void SetRed(const float r)
	{
		SetRed(static_cast<std::uint8_t>(r * 255));
	}

	constexpr void SetGreen(const float g)
	{
		SetGreen(static_cast<std::uint8_t>(g * 255));
	}

	constexpr void SetBlue(const float b)
	{
		SetBlue(static_cast<std::uint8_t>(b * 255));
	}

	constexpr void SetAlpha(const float a)
	{
		SetAlpha(static_cast<std::uint8_t>(a * 255));
	}

	constexpr void SetPacked(const std::uint32_t pack) { m_value = pack; }
	constexpr std::uint32_t GetPacked() const { return m_value; }

	bool operator==(const Color rhs) const;
	bool operator!=(const Color rhs) const { return !operator==(rhs); }

public:
	static const Color WHITE;
	static const Color BLACK;
	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;
	static const Color YELLOW;
	static const Color CYAN;
	static const Color MAGENTA;
};
}  // namespace yz
