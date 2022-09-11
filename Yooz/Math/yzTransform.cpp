#include <Math/yzTransform.hpp>

namespace yz
{
Transform& Transform::Translate(const float x, const float y)
{
	m[2] += x * m[0] + y * m[1];
	m[5] += x * m[3] + y * m[4];
	return *this;
}

Transform& Transform::Scale(const float x, const float y)
{
	m[0] *= x;
	m[1] *= y;
	m[3] *= x;
	m[4] *= y;
	return *this;
}

Transform& Transform::Rotate(float angle)
{
	float c  = std::cos(angle);
	float s  = std::sin(angle);
	float sx = m[0];
	float m1 = m[1];
	float m2 = m[3];
	float sy = m[4];

	m[0] = c * sx + s * m1;
	m[1] = -s * sx + c * m1;
	m[3] = c * m2 + s * sy;
	m[4] = -s * m2 + c * sy;
	return *this;
}

Transform& Transform::Project(float width, float height)
{
	float tw = 2.0f / width;
	float th = -2.0f / height;

	m[2] += (m[1] - m[0]);
	m[5] += (m[4] - m[3]);
	m[0] *= tw;
	m[1] *= th;
	m[3] *= tw;
	m[4] *= th;
	return *this;
}

}  // namespace yz
