#include <Math/yzFunctions.hpp>

namespace yz
{
float Deg2Rad(float deg) { return deg * CPI_180; }
float Rad2Deg(float rad) { return rad * C180_PI; }

float Lerp(float a, float b, float t) { return (1.0f - t) * a + t * b; }

float SmoothStep(float a, float b, float t)
{
	t = Clamp((t - a) / (b - a), 0.0f, 1.0f);
	return t * t * (3.0f - 2.0f * t);
}

float SmootherStep(float a, float b, float t)
{
	t = Clamp((t - a) / (b - a), 0.0f, 1.0f);
	return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
}
}  // namespace yz
