#pragma once

#include <Math/yzConstants.hpp>

#include <yzStds.hpp>

namespace yz
{
constexpr float Deg2Rad(float deg) { return deg * CPI_180; }
constexpr float Rad2Deg(float rad) { return rad * C180_PI; }

template<typename T>
constexpr const T& Clamp(const T& v, const T& l, const T& h)
{
	return v < l ? l : (h < v ? h : v);
}

template<typename T>
constexpr const T& Max(const T& a, const T& b)
{
	return a < b ? b : a;
}

template<typename T>
constexpr const T& Min(const T& a, const T& b)
{
	return a < b ? a : b;
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

constexpr float Lerp(float a, float b, float t) { return (1.0f - t) * a + t * b; }

template<typename T>
constexpr 
typename std::enable_if<std::is_integral<T>::value, const T>::type
Lerp(const T a, const T b, const T t)
{
	return a + t * (b - a);
}
// clang-format on

float SmoothStep(float a, float b, float t);

float SmootherStep(float a, float b, float t);

}  // namespace yz
