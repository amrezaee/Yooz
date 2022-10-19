#pragma once

#include <yzSTD.hpp>

#define LOGURU_RTTI 0
#include <loguru/loguru.hpp>

namespace yz
{
enum class Verbosity
{
	Off   = -9,
	Fatal = -3,
	Error = -2,
	Warn  = -1,
	Info  = 0,
	Trace = 1,
	Debug = 2,
	Max   = 9,
};

class Logger
{
public:
	static void Init(int argc, char** argv);

	static void SetVerbosity(Verbosity v);

	static void SetFilePreamble(bool enable);
	static void SetVerbosityPreamble(bool enable);
};

}  // namespace yz

#define YZ_DEBUG(...) DLOG_F(1, "\033[38;5;248m" __VA_ARGS__)

#define YZ_INFO(...)  LOG_F(INFO, "\033[38;5;2m" __VA_ARGS__)
#define YZ_SINFO(...) LOG_SCOPE_F(INFO, "\033[38;5;2m" __VA_ARGS__)

#define YZ_WARN(...)  LOG_F(WARNING, __VA_ARGS__)
#define YZ_SWARN(...) LOG_SCOPE_F(WARNING, __VA_ARGS__)

#define YZ_ERROR(...)  LOG_F(ERROR, __VA_ARGS__)
#define YZ_SERROR(...) LOG_SCOPE_F(ERROR, __VA_ARGS__)

#define YZ_FATAL(...)  LOG_F(FATAL, __VA_ARGS__)
#define YZ_SFATAL(...) LOG_SCOPE_F(FATAL, __VA_ARGS__)
