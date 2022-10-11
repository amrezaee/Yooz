#pragma once

#include <yzSTD.hpp>

namespace yz
{
// TODO: add %, bitwise, stream extraction and ...
template<typename T>
struct Vector2
{
	T x, y;

	constexpr Vector2(const Vector2<T>&)     = default;
	constexpr Vector2(Vector2<T>&&)          = default;
	Vector2<T>& operator=(const Vector2<T>&) = default;
	Vector2<T>& operator=(Vector2<T>&&)      = default;

	template<typename A>
	constexpr Vector2(const Vector2<A>& v): Vector2(v.x, v.y)
	{
	}

	template<typename A>
	inline Vector2<T>& operator=(const Vector2<A>& v)
	{
		x = static_cast<T>(v.x);
		y = static_cast<T>(v.y);
		return *this;
	}

	constexpr Vector2(): x(0), y(0) {}

	constexpr Vector2(T s): x(s), y(s) {}

	constexpr Vector2(T nx, T ny): x(nx), y(ny) {}

	template<typename A>
	constexpr Vector2(A a): x(static_cast<T>(a)), y(static_cast<T>(a))
	{
	}

	template<typename A, typename B>
	constexpr Vector2(A a, B b): x(static_cast<T>(a)), y(static_cast<T>(b))
	{
	}

	explicit constexpr Vector2(T* p): x(p[0]), y(p[1]) {}

	template<typename A>
	explicit constexpr Vector2(A* pa)
	        : x(static_cast<T>(pa[0])), y(static_cast<T>(pa[1]))
	{
	}



	template<typename U>
	constexpr T Dot(const Vector2<U> r) const
	{
		return static_cast<T>(r.x) * x + static_cast<T>(r.y) * y;
	}

	constexpr T Dot(const Vector2<T> r) const { return x * r.x + y * r.y; }

	constexpr T LengthSqrd() const { return x * x + y * y; }
	T           Length() const { return static_cast<T>(std::sqrt(x * x + y * y)); }

	void Normalize()
	{
		T t = Length();
		if(t == static_cast<T>(0))
			return;
		x /= t;
		y /= t;
	}

	Vector2<T> Normalize() const
	{
		Vector2<T> v = *this;
		return v.Normalize();
	}

	constexpr bool IsNorm() const { return Length() == static_cast<T>(1); }

	constexpr const T* GetPtr() const { return &x; }


	inline T& operator[](int i) { return i ? y : x; }
	inline T  operator[](int i) const { return i ? y : x; }

	constexpr Vector2<T> operator+() const { return *this; }
	constexpr Vector2<T> operator-() const { return Vector2<T>(-x, -y); }

	inline Vector2<T>& operator++()
	{
		++x;
		++y;
		return *this;
	}
	inline Vector2<T>& operator--()
	{
		--x;
		--y;
		return *this;
	}

	inline Vector2<T> operator++(int)
	{
		Vector2<T> v = *this;
		++x;
		++y;
		return v;
	}
	inline Vector2<T> operator--(int)
	{
		Vector2<T> v = *this;
		--x;
		--y;
		return v;
	}

	constexpr explicit operator bool() const
	{
		return (x != static_cast<T>(0)) && (y != static_cast<T>(0));
	}

	constexpr bool operator==(const Vector2<T>& r) const
	{
		return x == r.x && y == r.y;
	}
	constexpr bool operator!=(const Vector2<T>& r) const
	{
		return x != r.x || y != r.y;
	}
	constexpr bool operator>=(const Vector2<T>& r) const
	{
		return x >= r.x && y >= r.y;
	}
	constexpr bool operator<=(const Vector2<T>& r) const
	{
		return x <= r.x && y <= r.y;
	}
	constexpr bool operator<(const Vector2<T>& r) const
	{
		return x < r.x && y < r.y;
	}
	constexpr bool operator>(const Vector2<T>& r) const
	{
		return x > r.x && y > r.y;
	}
	constexpr Vector2<T> operator&&(const Vector2<T>& r) const
	{
		return Vector2<T>(x && r.x, y && r.y);
	}
	constexpr Vector2<T> operator||(const Vector2<T>& r) const
	{
		return Vector2<T>(x || r.x, y || r.y);
	}
};

template<typename T>
constexpr Vector2<T> operator+(const Vector2<T>& l, const Vector2<T>& r)
{
	return Vector2<T>(l.x + r.x, l.y + r.y);
}

template<typename T>
constexpr Vector2<T> operator-(const Vector2<T>& l, const Vector2<T>& r)
{
	return Vector2<T>(l.x - r.x, l.y - r.y);
}

template<typename T>
constexpr Vector2<T> operator*(const Vector2<T>& l, const Vector2<T>& r)
{
	return Vector2<T>(l.x * r.x, l.y * r.y);
}

template<typename T>
inline Vector2<T> operator/(const Vector2<T>& l, const Vector2<T>& r)
{
	return Vector2<T>(l.x / r.x, l.y / r.y);
}

template<typename T>
inline Vector2<T>& operator+=(Vector2<T>& l, const Vector2<T>& r)
{
	l.x += r.x;
	l.y += r.y;
	return l;
}

template<typename T>
inline Vector2<T>& operator-=(Vector2<T>& l, const Vector2<T>& r)
{
	l.x -= r.x;
	l.y -= r.y;
	return l;
}

template<typename T>
inline Vector2<T>& operator*=(Vector2<T>& l, const Vector2<T>& r)
{
	l.x *= r.x;
	l.y *= r.y;
	return l;
}

template<typename T>
inline Vector2<T>& operator/=(Vector2<T>& l, const Vector2<T>& r)
{
	l.x /= r.x;
	l.y /= r.y;
	return l;
}
// these are vec-vec operations
// scalar-vec or vec-scalar operations also use this overloadings
// because of implicit conversion

using Vec2 = Vector2<float>;
static_assert(sizeof(Vec2) == (2 * sizeof(float)), "wrong size");

using Vec2i = Vector2<std::int32_t>;
static_assert(sizeof(Vec2i) == (2 * sizeof(std::int32_t)), "wrong size");

using Vec2u = Vector2<std::uint32_t>;
static_assert(sizeof(Vec2u) == (2 * sizeof(std::uint32_t)), "wrong size");
}  // namespace yz
