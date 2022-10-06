#pragma once

#include <yzSTD.hpp>

namespace yz
{
enum class LogLevel
{
	Max,  // NOTE: don't pass this to Log
	Trace,
	Debug,
	Info,
	Warn,
	Error,
	Fatal,
	None  // NOTE: don't pass this to Log
};

class Logger
{
private:
	Logger() = default;

public:
	~Logger();

	static Logger& Get();

	void EnableFileLogging(const std::string& file);
	void DisableFileLogging();

	void SetConsoleLogging(bool on);

	void     SetLevel(LogLevel target);
	LogLevel GetLevel() const;

	void SetLevelPreamble(bool on);
	void SetFuncPreamble(bool on);
	void SetFilePreamble(bool on);
	void SetLinePreamble(bool on);

	template<typename... Args>
	void Log(const LogLevel target, const char* const func, const char* const file,
	         int line, const char* const fmt, const Args&... args);

	inline void Log(const LogLevel target, const char* const func,
	                const char* const file, int line, const char* const str)
	{
		Log(target, func, file, line, str, 0);
	}

	template<typename T>
	inline void Log(const LogLevel target, const char* const func,
	                const char* const file, int line,
	                const std::basic_string<T>& str)
	{
		Log(target, func, file, line, str.c_str(), 0);
	}

private:
	template<typename T>
	inline T Argument(T value)
	{
		return value;
	}

	template<typename T>
	inline const T* Argument(const std::basic_string<T>& value)
	{
		return value.c_str();
	}

	bool IsLevelDisabled(const LogLevel level);

	// TODO: remove this and use path type
	const char* GetBaseName(const char* path);

	template<typename... Args>
	void FormatString(const LogLevel target, const char* const file,
	                  const char* const func, int line, const char* const fmt,
	                  Args&... args);

private:
	static constexpr std::size_t m_buffer_size {512};
	char                         m_buffer[m_buffer_size] = {};

	LogLevel m_level {LogLevel::Max};

	bool m_preamble_level {true};
	bool m_preamble_func {true};
	bool m_preamble_file {true};
	bool m_preamble_line {true};

	bool        m_console_logging {true};
	bool        m_file_logging {false};
	std::string m_filename;
	std::FILE*  m_file {nullptr};

	const char* const m_colors[6] = {
	        "\033[38;2;200;200;200m", "\033[38;2;255;255;255m",
	        "\033[38;2;0;200;0m",     "\033[38;2;200;200;0m",
	        "\033[38;2;200;0;0m",     "\033[38;2;0;0;0;48;2;200;0;0m"};

	const char* const m_level_names[6] = {"Trace", "Debug", "Info",
	                                      "Warn",  "Error", "Fatal"};
};

template<typename... Args>
inline void Logger::Log(const LogLevel target, const char* const func,
                        const char* const file, int line, const char* const fmt,
                        const Args&... args)
{
	if(IsLevelDisabled(target))
		return;
	FormatString(target, file, func, line, fmt, args...);

	if(m_console_logging)
	{
		std::fputs(m_colors[int(target) - 1], stdout);
		std::fputs(m_buffer, stdout);
		std::fputs("\033[0m\n", stdout);
	}
	if(m_file_logging)
	{
		std::fputs(m_buffer, m_file);
		std::fputs("\n", m_file);
	}
}

template<typename... Args>
inline void Logger::FormatString(const LogLevel target, const char* const file,
                                 const char* const func, int line,
                                 const char* const fmt, Args&... args)
{
	std::size_t l            = 0;
	std::size_t s            = m_buffer_size;
	std::size_t preamble_len = 0;
	char*       buf          = m_buffer;

	if(m_preamble_file || m_preamble_line || m_preamble_func)
	{
		l = static_cast<std::size_t>(std::snprintf((buf += l), (s -= l), "["));
		++preamble_len;
	}

	if(m_preamble_func)
	{
		l = static_cast<std::size_t>(
		        std::snprintf((buf += l), (s -= l), "%s", func));
		preamble_len += l - 1;
		if(m_preamble_file || m_preamble_line)
		{
			l = static_cast<std::size_t>(std::snprintf((buf += l), (s -= l), ":"));
			++preamble_len;
		}
	}

	if(m_preamble_file)
	{
		l = static_cast<std::size_t>(
		        std::snprintf((buf += l), (s -= l), "%s", GetBaseName(file)));
		preamble_len += l - 1;
		if(m_preamble_line)
		{
			l = static_cast<std::size_t>(std::snprintf((buf += l), (s -= l), ":"));
			++preamble_len;
		}
	}

	if(m_preamble_line)
	{
		l = static_cast<std::size_t>(
		        std::snprintf((buf += l), (s -= l), "%d", line));
		preamble_len += l - 1;
	}

	if(m_preamble_file || m_preamble_line || m_preamble_func)
	{
		l = static_cast<std::size_t>(std::snprintf((buf += l), (s -= l), "]"));
		++preamble_len;
	}

	int width = 50 - static_cast<int>(preamble_len) - 5;

	if(m_preamble_level)
		l = static_cast<std::size_t>(std::snprintf((buf += l), (s -= l), "%*s | ",
		                                           width,
		                                           m_level_names[int(target) - 1]));
	else
		l = static_cast<std::size_t>(
		        std::snprintf((buf += l), (s -= l), "%*s", width, "| "));
	std::snprintf((buf += l), (s -= l), fmt, Argument(args)...);
}
}  // namespace yz

#define YZ_TRACE(...)                                                        \
	yz::Logger::Get().Log(yz::LogLevel::Trace, __func__, __FILE__, __LINE__, \
	                      __VA_ARGS__)

#define YZ_DEBUG(...)                                                        \
	yz::Logger::Get().Log(yz::LogLevel::Debug, __func__, __FILE__, __LINE__, \
	                      __VA_ARGS__)

#define YZ_INFO(...)                                                        \
	yz::Logger::Get().Log(yz::LogLevel::Info, __func__, __FILE__, __LINE__, \
	                      __VA_ARGS__)

#define YZ_WARN(...)                                                        \
	yz::Logger::Get().Log(yz::LogLevel::Warn, __func__, __FILE__, __LINE__, \
	                      __VA_ARGS__)


#define YZ_ERROR(...)                                                        \
	yz::Logger::Get().Log(yz::LogLevel::Error, __func__, __FILE__, __LINE__, \
	                      __VA_ARGS__)

#define YZ_FATAL(...)                                                        \
	yz::Logger::Get().Log(yz::LogLevel::Fatal, __func__, __FILE__, __LINE__, \
	                      __VA_ARGS__)
