#pragma once

#include <Math/yzVector2.hpp>

namespace yz
{
struct Transform
{
private:
	float m[6];

public:
	constexpr Transform(const Transform&) = default;
	constexpr Transform(Transform&&)      = default;
	constexpr Transform& operator=(const Transform&) = default;
	constexpr Transform& operator=(Transform&&) = default;

	constexpr Transform(): m {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f} {}

	explicit constexpr Transform(float s): m {s, 0.f, 0.f, 0.f, s, 0.f} {}

	template<typename A>
	explicit constexpr Transform(A a): Transform(static_cast<float>(a))
	{
	}

	constexpr Transform(float m1, float m2, float m3, float m4, float m5,
	                    float m6):
	        m {m1, m2, m3, m4, m5, m6}
	{
	}

	template<typename A, typename B, typename C, typename D, typename E,
	         typename F>
	constexpr Transform(A m1, B m2, C m3, D m4, E m5, F m6):
	        m {static_cast<float>(m1), static_cast<float>(m2),
	           static_cast<float>(m3), static_cast<float>(m4),
	           static_cast<float>(m5), static_cast<float>(m6)}
	{
	}

	void print()
	{
		printf("\n%.2f  %.2f  %.2f \n%.2f  %.2f  %.2f\n\n", double(m[0]), double(m[1]), double(m[2]), double(m[3]), double(m[4]),
		       double(m[5]));
	}

	inline const float* GetPtr() const { return m; }

	Transform&        Translate(const float x, const float y);
	inline Transform& Translate(const vec2 v) { return Translate(v.x, v.y); }
	inline Transform& Translate(const float s) { return Translate(s, s); }

	Transform&        Scale(const float x, const float y);
	inline Transform& Scale(const vec2 v) { return Scale(v.x, v.y); }
	inline Transform& Scale(const float s) { return Scale(s, s); }

	// angle in radians
	Transform& Rotate(float angle);

	Transform& Project(float width, float height);
	// TODO: fix this
	inline Transform& Project(vec2 v) { return Project(v.x, v.y); }
};
}  // namespace yz
