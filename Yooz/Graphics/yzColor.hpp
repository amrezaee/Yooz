#pragma once

#include <yzpch.hpp>

namespace yz
{
// 32bit packed Color type in RGBA format
class Color
{
private:
	std::uint32_t m_value {0u};

public:
	constexpr Color()              = default;
	constexpr Color(const Color&)  = default;
	constexpr Color(Color&&)       = default;
	Color& operator=(const Color&) = default;
	Color& operator=(Color&&)      = default;

	constexpr Color(std::uint32_t color): m_value(color) {}

	constexpr Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
	        :

	          m_value(static_cast<std::uint32_t>(r << 24u) |
	                  static_cast<std::uint32_t>(g << 16u) |
	                  static_cast<std::uint32_t>(b << 8u) |
	                  static_cast<std::uint32_t>(a))
	{
	}

	constexpr Color(float r, float g, float b, float a)
	        : Color(static_cast<std::uint8_t>(r * 255u),
	                static_cast<std::uint8_t>(g * 255u),
	                static_cast<std::uint8_t>(b * 255u),
	                static_cast<std::uint8_t>(a * 255u))
	{
	}

	constexpr Color(std::uint8_t r, std::uint8_t g, std::uint8_t b)
	        : Color(r, g, b, 255u)
	{
	}

	constexpr Color(float r, float g, float b): Color(r, g, b, 1.0f) {}

	constexpr Color(Color color, std::uint8_t alpha)
	        : m_value((color.m_value << 8) | alpha)
	{
	}

	constexpr Color(Color color, float alpha)
	        : Color(color, static_cast<std::uint8_t>(alpha * 255u))
	{
	}

	void Set(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a);

	void Set(float r, float g, float b, float a);

	void Set(std::uint8_t r, std::uint8_t g, std::uint8_t b);

	void Set(float r, float g, float b);

	void GetColors(float* const out) const;

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

	void SetRed(std::uint8_t r);
	void SetGreen(std::uint8_t g);
	void SetBlue(std::uint8_t b);
	void SetAlpha(std::uint8_t a);

	void SetRed(float r);
	void SetGreen(float g);
	void SetBlue(float b);
	void SetAlpha(float a);

	void                    SetPacked(const std::uint32_t pack);
	constexpr std::uint32_t GetPacked() const { return m_value; }

	bool operator==(Color rhs) const;
	bool operator!=(Color rhs) const { return !operator==(rhs); }

public:
	static const Color WHITE;
	static const Color TRANS_WHITE;
	static const Color BLACK;
	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;
	static const Color YELLOW;
	static const Color CYAN;
	static const Color MAGENTA;
	static const Color BROWN;
	static const Color PURPLE;

	static const Color ALICE_BLUE;
	static const Color ANTIQUE_WHITE;
	static const Color AQUA;
	static const Color AQUAMARINE;
	static const Color AZURE;
	static const Color BLUE_VIOLET;
	static const Color BURLYWOOD;
	static const Color CADET_BLUE;
	static const Color CHARTREUSE;
	static const Color CHOCOLATE;
	static const Color CORNFLOWER_BLUE;
	static const Color CORNSILK;
	static const Color CRIMSON;
	static const Color DARK_ORCHID;
	static const Color DARK_SALAMON;
	static const Color DEEP_PINK;
	static const Color FLORAL_WHITE;
	static const Color GHOST_WHITE;
	static const Color GOLD;
	static const Color INDIGO;
	static const Color IVORY;
	static const Color LAVENDER;
	static const Color LAWN_GREEN;
	static const Color LIGHT_CORAL;
	static const Color MOCCASIN;
	static const Color PLUM;
	static const Color POWDER_BLUE;
	static const Color ROYAL_BLUE;
	static const Color ROSY_BROWN;
	static const Color SLATE_BLUE;
	static const Color SNOW;
	static const Color TEAL;
	static const Color TURQUOISE;
	static const Color WHITE_SMOKE;
	static const Color YELLOW_GREEN;
};
}  // namespace yz
