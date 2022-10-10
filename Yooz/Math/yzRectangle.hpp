#pragma once

#include <Math/yzVector2.hpp>

namespace yz
{
template<typename T>
struct Rectangle
{
public:
	T x {0};
	T y {0};
	T w {0};
	T h {0};

	constexpr Rectangle(const Rectangle&)            = default;
	constexpr Rectangle(Rectangle&&)                 = default;
	constexpr Rectangle& operator=(const Rectangle&) = default;
	constexpr Rectangle& operator=(Rectangle&&)      = default;

	constexpr Rectangle(const T px, const T py, const T pw, const T ph):
	        x(px), y(py), w(pw), h(ph)
	{
	}

	template<typename A, typename B, typename C, typename D>
	constexpr Rectangle(const A a, const B b, const C c, const D d):
	        x(static_cast<T>(a)), y(static_cast<T>(b)), w(static_cast<T>(c)),
	        h(static_cast<T>(d))
	{
	}

	template<typename A>
	constexpr Rectangle(const A px, const A py, const A pw, const A ph):
	        x(static_cast<T>(px)), y(static_cast<T>(py)), w(static_cast<T>(pw)),
	        h(static_cast<T>(ph))
	{
	}

	constexpr Vector2<T> GetPos() const { return Vector2<T>(x, y); }
	constexpr Vector2<T> GetSize() const { return Vector2<T>(w, h); }

	void SetPos(const T px, const T py)
	{
		x = px;
		y = py;
	}
	void SetPos(const Vector2<T>& v) { SetPos(v.x, v.y); }
	void SetSize(const T pw, const T ph)
	{
		w = pw;
		h = ph;
	}
	void SetSize(const Vector2<T>& v) { SetSize(v.x, v.y); }
};

using Rect  = Rectangle<float>;
using Recti = Rectangle<std::int32_t>;
using Rectu = Rectangle<std::uint32_t>;
}  // namespace yz
