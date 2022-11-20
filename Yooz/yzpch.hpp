#pragma once

#include <stdint.h>
#include <stdlib.h>

#include <algorithm>
#include <bitset>
#include <chrono>
#include <iostream>
#include <memory>
#include <numeric>
#include <sstream>
#include <string>
#include <system_error>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#include <cmath>
#include <cstddef>
#include <cstdio>
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

template<class T, ::size_t N>
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
typename _Unique_if<T>::_Unknown_bound make_unique(::size_t n)
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

#ifdef YZ_GL_PLATFORM
	#include <glad/gl.h>
#endif

#include <SDL.h>

#include <ghc/filesystem.hpp>
namespace fs = ghc::filesystem;
