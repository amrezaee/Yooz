// Precompiled header for standard library
#pragma once

#include <algorithm>
#include <bitset>
#include <chrono>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// use namespace xtd for make_unique
#if __cplusplus == 201103L
namespace xtd
{
template<class T>
struct _Unique_if
{
	typedef ::std::unique_ptr<T> _Single_object;
};

template<class T>
struct _Unique_if<T[]>
{
	typedef ::std::unique_ptr<T[]> _Unknown_bound;
};

template<class T, ::std::size_t N>
struct _Unique_if<T[N]>
{
	typedef void _Known_bound;
};

template<class T, class... Args>
typename _Unique_if<T>::_Single_object make_unique(Args&&... args)
{
	return ::std::unique_ptr<T>(new T(::std::forward<Args>(args)...));
}

template<class T>
typename _Unique_if<T>::_Unknown_bound make_unique(::std::size_t n)
{
	typedef typename ::std::remove_extent<T>::type U;
	return ::std::unique_ptr<T>(new U[n]());
}

template<class T, class... Args>
typename _Unique_if<T>::_Known_bound make_unique(Args&&...) = delete;

}  // namespace xtd

#else
namespace xtd = std;
#endif
