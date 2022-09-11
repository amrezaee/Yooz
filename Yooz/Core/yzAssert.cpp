#include <Core/yzAssert.hpp>

#include <Platform/yzMessageBox.hpp>

#include <yzStds.hpp>

#ifndef YZ_DISABLE_ASSERTION

constexpr std::size_t buffer_size         = 256;
char                  buffer[buffer_size] = {'\0'};

void yzOutputAssertionFailure(const char* const expr, const char* const msg,
                              const char* const file, const int line)
{
	if(*msg)
	{
		std::snprintf(buffer, buffer_size, "ASSERTION FAILED\n %s", msg);
		yz::MessageBoxFatal(buffer);
	}
	else
	{
		// TODO: REMOVE THIS
		const char* filename = std::strrchr(file, '/');
		if(!filename)
			filename = std::strrchr(file, '\\') + 1;
		else
			++filename;

		std::snprintf(buffer, buffer_size, "ASSERTION %s FAILED at  %s:%d",
		              expr, ++filename, line);
		yz::MessageBoxFatal(buffer);
	}
}

#endif
