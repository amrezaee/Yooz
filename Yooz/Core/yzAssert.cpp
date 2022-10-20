#include <Core/yzAssert.hpp>

#include <Core/yzLogger.hpp>

#include <yzpch.hpp>

#ifndef YZ_DISABLE_ASSERTION

void yzOutputAssertionFailure(const char* expr, const char* msg, const char* file,
                              const int line)
{
	if(*msg)  // with message
	{
		YZ_FATAL("%s", msg);
	}
	else  // without message
	{
		fs::path p(file);
		YZ_FATAL("Assertion %s Failed at  %s:%d", expr,
		         p.filename().generic_string().c_str(), line);
	}
}

#endif
