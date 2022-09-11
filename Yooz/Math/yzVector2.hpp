#pragma once

#include <yzStds.hpp>

namespace yz
{
// TODO: add %, bitwise, stream extraction and ...
template<typename T>
struct Vector2
{
	T x;
	T y;

	constexpr Vector2(const Vector2<T>&) = default;
	constexpr Vector2(Vector2<T>&&)      = default;
	constexpr Vector2<T>& operator=(const Vector2<T>&) = default;
	constexpr Vector2<T>& operator=(Vector2<T>&&) = default;
	~Vector2()                                    = default;

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

	constexpr Vector2(): x(static_cast<T>(0)), y(static_cast<T>(0)) {}

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
	explicit constexpr Vector2(A* pa):
	        x(static_cast<T>(pa[0])), y(static_cast<T>(pa[1]))
	{
	}



	template<typename U>
	constexpr T dot(const Vector2<U> r) const
	{
		return static_cast<T>(r.x) * x + static_cast<T>(r.y) * y;
	}
	constexpr T dot(const Vector2<T> r) const { return x * r.x + y * r.y; }

	constexpr T LengthSqrd() const { return x * x + y * y; }
	constexpr T Length() const { return std::sqrt(x * x + y * y); }

	inline void Normalize()
	{
		T t = Length();
		ASSERT(t != 0);
		x /= t;
		y /= t;
	}
	
	inline  Vector2<T> Normalize() const
	{
		T t = Length();
		ASSERT(t != 0);
		return Vector2<T>(x / t, y / t);
	}
	constexpr bool IsNorm() const { return Length() == static_cast<T>(1); }



	// TODO: fix this
	constexpr const T* GetPtr() const { return x; }

	inline T& operator[](int i)
	{
		ASSERT(i == 0 || i == 1);
		return i ? y : x;
	}
	inline T operator[](int i) const
	{
		ASSERT(i == 0 || i == 1);
		return i ? y : x;
	}

	constexpr Vector2<T> operator+() const { return *this; }
	constexpr Vector2<T> operator-() const { return Vector2<T>(-x, -y); }

	inline Vector2<T>& operator++()
	{
		x++;
		y++;
		return *this;
	}
	inline Vector2<T>& operator--()
	{
		x--;
		y--;
		return *this;
	}

	inline Vector2<T> operator++(int)
	{
		Vector2<T> v = *this;
		x++;
		y++;
		return v;
	}
	inline Vector2<T> operator--(int)
	{
		Vector2<T> v = *this;
		x--;
		y--;
		return v;
	}

	constexpr operator bool() const
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
	ASSERT(r.x != 0 && r.y != 0);
	return Vector2<T>(l.x / r.x, l.y / r.y);
}

template<typename T>
inline Vector2<T>& operator+=(const Vector2<T>& l, const Vector2<T>& r)
{
	l.x += r.x;
	l.y += r.y;
	return l;
}

template<typename T>
inline Vector2<T>& operator-=(const Vector2<T>& l, const Vector2<T>& r)
{
	l.x -= r.x;
	l.y -= r.y;
	return l;
}

template<typename T>
inline Vector2<T>& operator*=(const Vector2<T>& l, const Vector2<T>& r)
{
	l.x *= r.x;
	l.y *= r.y;
	return l;
}

template<typename T>
inline Vector2<T>& operator/=(const Vector2<T>& l, const Vector2<T>& r)
{
	ASSERT(r.x != 0 && r.y != 0);
	l.x /= r.x;
	l.y /= r.y;
	return l;
}
// these are vec-vec operations
// scalar-vec or vec-scalar operations also use this overloadings
// because of implicit conversion

using vec2 = Vector2<float>;
static_assert(sizeof(vec2) == (2 * sizeof(float)), "wrong size");

using vec2i = Vector2<std::int32_t>;
static_assert(sizeof(vec2i) == (2 * sizeof(std::int32_t)), "wrong size");

using vec2u = Vector2<std::uint32_t>;
static_assert(sizeof(vec2u) == (2 * sizeof(std::uint32_t)), "wrong size");

using vec2b = Vector2<bool>;
static_assert(sizeof(vec2b) == (2 * sizeof(bool)), "wrong size");
}  // namespace yz
