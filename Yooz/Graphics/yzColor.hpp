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
	constexpr Color()             = default;
	constexpr Color(const Color&) = default;
	constexpr Color(Color&&)      = default;
	constexpr Color& operator=(const Color&) = default;
	constexpr Color& operator=(Color&&) = default;

	constexpr Color(const std::uint32_t color): m_value(color) {}

	constexpr Color(const std::uint8_t r, const std::uint8_t g,
	                const std::uint8_t b, const std::uint8_t a):
	        m_value(std::uint32_t(r << 24u) | std::uint32_t(g << 16u) |
	                std::uint32_t(b << 8u) | std::uint32_t(a))
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

	std::uint8_t GetRed() const;
	std::uint8_t GetGreen() const;
	std::uint8_t GetBlue() const;
	std::uint8_t GetAlpha() const;

	void SetRed(std::uint8_t r);
	void SetGreen(std::uint8_t g);
	void SetBlue(std::uint8_t b);
	void SetAlpha(std::uint8_t a);

	void SetRed(float r) { SetRed(static_cast<std::uint8_t>(r * 255)); }
	void SetGreen(float g) { SetGreen(static_cast<std::uint8_t>(g * 255)); }
	void SetBlue(float b) { SetBlue(static_cast<std::uint8_t>(b * 255)); }
	void SetAlpha(float a) { SetAlpha(static_cast<std::uint8_t>(a * 255)); }

	void          SetPacked(std::uint32_t pack) { m_value = pack; }
	std::uint32_t GetPacked() const { return m_value; }

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
