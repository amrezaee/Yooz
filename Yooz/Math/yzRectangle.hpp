#pragma once

#include <Math/yzVector2.hpp>

namespace yz
{
template<typename T>
struct Rectangle
{
public:
	T x, y, w, h;

	Rectangle(): x(0), y(0), w(0), h(0) {}
	Rectangle(const Rectangle&)            = default;
	Rectangle(Rectangle&&)                 = default;
	Rectangle& operator=(const Rectangle&) = default;
	Rectangle& operator=(Rectangle&&)      = default;

	Rectangle(T px, T py, T pw, T ph): x(px), y(py), w(pw), h(ph) {}

	template<typename A, typename B, typename C, typename D>
	Rectangle(A a, B b, C c, D d):
	        x(static_cast<T>(a)), y(static_cast<T>(b)), w(static_cast<T>(c)),
	        h(static_cast<T>(d))
	{
	}

	template<typename A>
	Rectangle(A px, A py, A pw, A ph):
	        x(static_cast<T>(px)), y(static_cast<T>(py)), w(static_cast<T>(pw)),
	        h(static_cast<T>(ph))
	{
	}

	Vector2<T> GetPos() { return Vector2<T>(x, y); }
	Vector2<T> GetSize() { return Vector2<T>(w, h); }
};

using rect  = Rectangle<float>;
using recti = Rectangle<std::int32_t>;
using rectu = Rectangle<std::uint32_t>;

}  // namespace yz
