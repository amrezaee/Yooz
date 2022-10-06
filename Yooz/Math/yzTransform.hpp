#pragma once

#include <Math/yzFunctions.hpp>
#include <Math/yzVector2.hpp>

namespace yz
{
struct Transform
{
private:
	float m[6];

public:
	constexpr Transform(const Transform&)            = default;
	constexpr Transform(Transform&&)                 = default;
	constexpr Transform& operator=(const Transform&) = default;
	constexpr Transform& operator=(Transform&&)      = default;

	constexpr Transform(): m {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f} {}

	explicit constexpr Transform(const float s): m {s, 0.f, 0.f, 0.f, s, 0.f} {}

	template<typename A>
	explicit constexpr Transform(const A a): Transform(static_cast<float>(a))
	{
	}

	constexpr Transform(const float m1, const float m2, const float m3,
	                    const float m4, const float m5, const float m6)
	        : m {m1, m2, m3, m4, m5, m6}
	{
	}

	template<typename A, typename B, typename C, typename D, typename E, typename F>
	constexpr Transform(const A m1, const B m2, const C m3, const D m4, const E m5,
	                    const F m6)
	        : m {static_cast<float>(m1), static_cast<float>(m2),
	             static_cast<float>(m3), static_cast<float>(m4),
	             static_cast<float>(m5), static_cast<float>(m6)}
	{
	}

	Transform(const float width, const float height): Transform()
	{
		Project(width, height);
	}

	Transform(const Vec2 size): Transform(size.x, size.y) {}

	Transform  operator*(const Transform& r) const;
	Transform& operator*=(const Transform& r);

	Vec2 operator*(const Vec2 v) const;
	void TransformVec2(const Vec2 v, Vec2& out) const;

	constexpr const float* GetPtr() const { return m; }

	Transform&        Translate(const float x, const float y);
	inline Transform& Translate(const Vec2 v) { return Translate(v.x, v.y); }
	inline Transform& Translate(const float s) { return Translate(s, s); }

	Transform&        Scale(const float x, const float y);
	inline Transform& Scale(const Vec2 v) { return Scale(v.x, v.y); }
	inline Transform& Scale(const float s) { return Scale(s, s); }

	Transform&        Shear(const float x, const float y);
	inline Transform& Shear(const Vec2 v) { return Shear(v.x, v.y); }
	inline Transform& Shear(const float f) { return Shear(f, f); }

	// angle in radians
	Transform&        Rotate(const float angle);
	inline Transform& RotateDegree(const float angle)
	{
		return Rotate(Deg2Rad(angle));
	}

	Transform&        Project(const float width, const float height);
	inline Transform& Project(const Vec2 v) { return Project(v.x, v.y); }
};
}  // namespace yz
