#include <Math/yzTransform.hpp>

namespace yz
{
void Transform::Reset()
{
	m[0] = 1.0f;
	m[1] = 0.0f;
	m[2] = 0.0f;
	m[3] = 0.0f;
	m[4] = 1.0f;
	m[5] = 0.0f;
}

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

Transform& Transform::Shear(const float x, const float y)
{
	float a = m[0];
	float b = m[1];
	float d = m[3];
	float e = m[4];

	m[0] += b * y;
	m[1] += a * x;
	m[3] += e * y;
	m[4] += d * x;
	return *this;
}

Transform& Transform::Rotate(const float angle)
{
	float c = std::cos(angle);
	float s = std::sin(angle);
	float a = m[0];
	float b = m[1];
	float d = m[3];
	float e = m[4];

	m[0] = +a * c + b * s;
	m[1] = -a * s + b * c;
	m[3] = +d * c + e * s;
	m[4] = -d * s + e * c;
	return *this;
}

Transform& Transform::Project(const float l, const float r, const float t,
                              const float b)
{
	float dx = (r - l);
	float dy = (t - b);
	float A  = 2.0f / dx;
	float B  = 2.0f / dy;
	float C  = (-r - l) / dx;
	float D  = (-t - b) / dy;

	m[2] += (C * m[0]) + (D * m[1]);
	m[5] += (C * m[3]) + (D * m[4]);
	m[0] *= A;
	m[1] *= B;
	m[3] *= A;
	m[4] *= B;
	return *this;
}

Transform& Transform::operator*=(const Transform& r)
{
	*this = Transform(m[0] * r.m[0] + m[1] * r.m[3], m[0] * r.m[1] + m[1] * r.m[4],
	                  m[0] * r.m[2] + m[1] * r.m[5] + m[2],
	                  m[3] * r.m[0] + m[4] * r.m[3], m[3] * r.m[1] + m[4] * r.m[4],
	                  m[3] * r.m[2] + m[4] * r.m[5] + m[5]);
	return *this;
}

Transform Transform::operator*(const Transform& r) const
{
	return Transform(m[0] * r.m[0] + m[1] * r.m[3], m[0] * r.m[1] + m[1] * r.m[4],
	                 m[0] * r.m[2] + m[1] * r.m[5] + m[2],
	                 m[3] * r.m[0] + m[4] * r.m[3], m[3] * r.m[1] + m[4] * r.m[4],
	                 m[3] * r.m[2] + m[4] * r.m[5] + m[5]);
}

Vec2 Transform::operator*(const Vec2 v) const
{
	return Vec2(v.x * m[0] + v.y * m[1] + m[2], v.x * m[3] + v.y * m[4] + m[5]);
}

void Transform::TransformVec2(const Vec2 v, Vec2& out) const
{
	out.x = v.x * m[0] + v.y * m[1] + m[2];
	out.y = v.x * m[3] + v.y * m[4] + m[5];
}
}  // namespace yz
