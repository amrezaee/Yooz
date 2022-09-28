#include <Math/yzFunctions.hpp>

namespace yz
{
float SmoothStep(const float a, const float b, const float t)
{
	float v = Clamp((t - a) / (b - a), 0.0f, 1.0f);
	return v * v * (3.0f - 2.0f * v);
}

float SmootherStep(const float a, const float b, const float t)
{
	float v = Clamp((t - a) / (b - a), 0.0f, 1.0f);
	return v * v * v * (v * (v * 6.0f - 15.0f) + 10.0f);
}

// Easing functions
float EaseInSin(const float x) { return 1.0f - std::cos(x * CPI * 0.5f); }
float EaseOutSin(const float x) { return std::sin(x * CPI * 0.5f); }
float EaseInOutSin(const float x) { return -(std::cos(x * CPI) - 1.0f) * 0.5f; }
float EaseOutQuart(const float x)
{
	float t = (x - 1.0f) * x;
	return 1.0f - t * t;
}
float EaseInOutQuart(const float x)
{
	if(x < 0.5f)
	{
		float t = x * x;
		return 8.0f * t * t;
	}
	else
	{
		float t = (x - 1.0f) * x;
		return 1.0f - 8.0f * t * t;
	}
}
}  // namespace yz
