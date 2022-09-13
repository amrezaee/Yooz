#pragma once
#include <cassert>

#include <Core/yzBase.hpp>

#ifndef YZ_DISABLE_ASSERTION

void yzOutputAssertionFailure(const char* const expr, const char* const msg,
                              const char* const file, const int line);

	#define YZ_ASSERT_IMPL_(expr)                                    \
		{                                                            \
			if(!(expr))                                              \
			{                                                        \
				yzOutputAssertionFailure(YZ_STR(expr), "", __FILE__, \
				                         __LINE__);                  \
				YZ_DEBUGBREAK();                                     \
			}                                                        \
		}

	#define YZ_ASSERT_MSG_IMPL_(expr, msg)                              \
		{                                                               \
			if(!(expr))                                                 \
			{                                                           \
				yzOutputAssertionFailure(YZ_STR(expr), (msg), __FILE__, \
				                         __LINE__);                     \
				YZ_DEBUGBREAK();                                        \
			}                                                           \
		}

	#define YZ_GET_MACRO_NAME_(_1, _2, macro, ...) macro
	#define YZ_GET_MACRO_(...)                                         \
		YZ_EXPAND(YZ_GET_MACRO_NAME_(__VA_ARGS__, YZ_ASSERT_MSG_IMPL_, \
		                             YZ_ASSERT_IMPL_))

	#define YZ_ASSERT(...) YZ_EXPAND(YZ_GET_MACRO_(__VA_ARGS__)(__VA_ARGS__))

#else
	#define YZ_ASSERT(...) ((void)0)
#endif
