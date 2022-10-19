#pragma once

#include <yzDeps.hpp>
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

	template<typename... Args>
	static void Log(Verbosity v, const char* fmt, const Args&... args)
	{
		VLOG_F(static_cast<int>(v), fmt, Argument(args)...);
	}

	template<typename... Args>
	static void LogDebug(const char* fmt, const Args&... args)
	{
		DVLOG_F(static_cast<int>(Verbosity::Debug), fmt, Argument(args)...);
	}

private:
	template<typename T>
	static T Argument(T t)
	{
		return t;
	}

	template<typename T>
	static const T* Argument(const std::basic_string<T>& s)
	{
		return s.c_str();
	}

	template<typename T>
	static const T* Argument(const fs::path& p)
	{
		return p.generic_string().c_str();
	}
};
}  // namespace yz

#define YZ_DEBUG(...) yz::Logger::LogDebug(__VA_ARGS__)

#define YZ_INFO(...)  yz::Logger::Log(yz::Verbosity::Info, __VA_ARGS__)
#define YZ_SINFO(...) LOG_SCOPE_F(INFO, __VA_ARGS__)

#define YZ_WARN(...)  yz::Logger::Log(yz::Verbosity::Warn, __VA_ARGS__)
#define YZ_SWARN(...) LOG_SCOPE_F(WARN, __VA_ARGS__)

#define YZ_ERROR(...)  yz::Logger::Log(yz::Verbosity::Error, __VA_ARGS__)
#define YZ_SERROR(...) LOG_SCOPE_F(ERROR, __VA_ARGS__)

#define YZ_FATAL(...)  yz::Logger::Log(yz::Verbosity::Fatal, __VA_ARGS__)
#define YZ_SFATAL(...) LOG_SCOPE_F(FATAL, __VA_ARGS__)
