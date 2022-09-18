#include <Math/yzFunctions.hpp>

namespace yz
{
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
