#pragma once

#include <Math/yzConstants.hpp>

#include <yzStds.hpp>

namespace yz
{
constexpr float Deg2Rad(const float deg) { return deg * CPI_180; }
constexpr float Rad2Deg(const float rad) { return rad * C180_PI; }

template<typename T>
constexpr const T& Clamp(const T& v, const T& l, const T& h)
{
	return (v < l) ? l : ((h < v) ? h : v);
}

template<typename T>
constexpr const T& Max(const T& a, const T& b)
{
	return (a < b) ? b : a;
}

template<typename T>
constexpr const T& Min(const T& a, const T& b)
{
	return (a < b) ? a : b;
}

// clang-format off
template<typename T>
constexpr 
typename std::enable_if<(std::is_integral<T>::value ||
                         std::is_floating_point<T>::value) &&
                        !std::is_unsigned<T>::value, const int>::type
Sign(const T v)
{
	return (static_cast<T>(0) < v) - (v < static_cast<T>(0));
}

constexpr float Lerp(const float a, const float b, const float t) { return (1.0f - t) * a + t * b; }

template<typename T>
constexpr 
typename std::enable_if<std::is_integral<T>::value, const T>::type
Lerp(const T a, const T b, const T t)
{
	return a + t * (b - a);
}
// clang-format on

float SmoothStep(const float a, const float b, const float t);

float SmootherStep(const float a, const float b, const float t);

// Easing functions
float EaseInSin(const float x);
float EaseOutSin(const float x);
float EaseInOutSin(const float x);

constexpr float EaseInQuad(const float x) { return x * x; }
constexpr float EaseOutQuad(const float x) { return x * (2.0f - x); }
constexpr float EaseInOutQuad(const float x)
{
	return (x < 0.5f) ? (2.0f * x * x) : (x * (4.0f - 2.0f * x) - 1.0f);
}

constexpr float EaseInCubic(const float x) { return x * x * x; }
constexpr float EaseOutCubic(const float x)
{
	return x * (x * x - 3.0f * x + 3.0f);
}
constexpr float EaseInOutCubic(const float x)
{
	return (x < 0.5f) ? (4.0f * x * x * x) :
	                    (x * (4.0f * x * x - 12.0f * x + 12.0f) - 3.0f);
}

constexpr float EaseInQuart(const float x) { return x * x * x * x; }
float           EaseOutQuart(const float x);
float           EaseInOutQuart(const float x);
}  // namespace yz
