#pragma once


namespace yz
{
using Handle = void*;
}

#define YZ_STR(s)    #s
#define YZ_EXPAND(x) x
#define YZ_UNUSED(x) (void)(x)

// TODO: USE YZ_* MACROS FOR PLATFORM DETECTION
#if defined(_MSC_VER)
extern void __cdecl __debugbreak(void);
	#define YZ_DEBUGBREAK() __debugbreak()
#elif((!defined(__NACL__)) && ((defined(__GNUC__) || defined(__clang__)) && \
                               (defined(__i386__) || defined(__x86_64__))))
	#define YZ_DEBUGBREAK() __asm__ __volatile__("int $3\n\t")
#elif(defined(__APPLE__) && (defined(__arm64__) || defined(__aarch64__)))
	#define YZ_DEBUGBREAK() __asm__ __volatile__("brk #22\n\t")
#elif defined(__APPLE__) && defined(__arm__)
	#define YZ_DEBUGBREAK() __asm__ __volatile__("bkpt #22\n\t")
#elif defined(__386__) && defined(__WATCOMC__)
	#define YZ_DEBUGBREAK()   \
		{                     \
			_asm { int 0x03 } \
		}
#elif defined(HAVE_SIGNAL_H) && !defined(__WATCOMC__)
	#include <signal.h>
	#define YZ_DEBUGBREAK() raise(SIGTRAP)
#else
	#define YZ_DEBUGBREAK() ((void)0)
#endif
