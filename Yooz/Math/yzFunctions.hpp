#pragma once

#include <Math/yzConstants.hpp>

#include <yzSTD.hpp>

namespace yz
{
constexpr float Deg2Rad(const float deg)
{
	return deg * CPI_180;
}
constexpr float Rad2Deg(const float rad)
{
	return rad * C180_PI;
}

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

float EaseInQuad(const float x);
float EaseOutQuad(const float x);
float EaseInOutQuad(const float x);

float EaseInCubic(const float x);
float EaseOutCubic(const float x);
float EaseInOutCubic(const float x);

float EaseInQuart(const float x);
float EaseOutQuart(const float x);
float EaseInOutQuart(const float x);

float EaseInQuint(const float x);
float EaseOutQuint(const float x);
float EaseInOutQuint(const float x);

float EaseInExpo(const float x);
float EaseOutExpo(const float x);
float EaseInOutExpo(const float x);

float EaseInCirc(const float x);
float EaseOutCirc(const float x);
float EaseInOutCirc(const float x);
}  // namespace yz
