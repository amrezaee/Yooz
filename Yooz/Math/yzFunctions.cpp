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
float EaseInSin(const float x)
{
	return 1.0f - std::cos(x * CPI_HALF);
}

float EaseOutSin(const float x)
{
	return std::sin(x * CPI_HALF);
}

float EaseInOutSin(const float x)
{
	return -0.5f * (std::cos(x * CPI) - 1.0f);
}

float EaseInQuad(const float x)
{
	return x * x;
}

float EaseOutQuad(const float x)
{
	return x * (2.0f - x);
}

float EaseInOutQuad(const float x)
{
	return (x < 0.5f) ? (2.0f * x * x) : (x * (4.0f - 2.0f * x) - 1.0f);
}

float EaseInCubic(const float x)
{
	return x * x * x;
}

float EaseOutCubic(const float x)
{
	float t = x - 1.0f;
	return 1.0f + t * t * t;
}

float EaseInOutCubic(const float x)
{
	return (x < 0.5f) ? (4.0f * x * x * x) :
	                    (x * (4.0f * x * x - 12.0f * x + 12.0f) - 3.0f);
}

float EaseInQuart(const float x)
{
	return x * x * x * x;
}

float EaseOutQuart(const float x)
{
	float t = (x - 1.0f) * (x - 1.0f);
	return 1.0f - t * t;
}

float EaseInOutQuart(const float x)
{
	float t;
	if(x < 0.5f)
	{
		t = x * x;
		return 8.0f * t * t;
	}
	else
	{
		t = (x - 1.0f) * (x - 1.0f);
		return 1.0f - 8.0f * t * t;
	}
}

float EaseInQuint(const float x)
{
	return x * x * x * x * x;
}

float EaseOutQuint(const float x)
{
	float t = (x - 1.0f) * (x - 1.0f);
	return 1.0f + t * t * (x - 1.0f);
}

float EaseInOutQuint(const float x)
{
	float t;
	if(x < 0.5f)
	{
		t = x * x;
		return 16.0f * x * t * t;
	}
	else
	{
		t = (x - 1.0f) * (x - 1.0f);
		return 1 + 16 * (x - 1.0f) * t * t;
	}
}

float EaseInExpo(const float x)
{
	return x == 0.0f ? 0.0f : std::pow(2.0f, 10.0f * x - 10.0f);
}

float EaseOutExpo(const float x)
{
	return x == 1.0f ? 1.0f : 1.0f - std::pow(2.0f, -10.0f * x);
}

float EaseInOutExpo(const float x)
{
	return x == 0.0f ? 0.0f :
	       x == 1.0f ? 1.0f :
	       x < 0.5f  ? std::pow(2.0f, 20.0f * x - 10.0f) * 0.5f :
	                   (2.0f - std::pow(2.0f, -20.0f * x + 10.0f)) * 0.5f;
}

float EaseInCirc(const float x)
{
	return 1.0f - std::sqrt(1.0f - x * x);
}

float EaseOutCirc(const float x)
{
	return std::sqrt(1.0f - (x - 1.0f) * (x - 1.0f));
}

float EaseInOutCirc(const float x)
{
	return x < 0.5f ? (1.0f - std::sqrt(1.0f - (2.0f * x) * (2.0f * x))) * 0.5f :
	                  (std::sqrt(1.0f - (-2.0f * x + 2.0f) * (-2.0f * x + 2.0f)) +
	                   1.0f) * 0.5f;
}
}  // namespace yz
