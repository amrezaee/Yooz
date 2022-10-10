#include <Core/yzLogger.hpp>

namespace yz
{
Logger::~Logger()
{
	if(!m_filename.empty()) std::fclose(m_file);
}

Logger& Logger::Get()
{
	static Logger logger;
	return logger;
}

void Logger::EnableFileLogging(const std::string& file)
{
	m_filename     = file;
	m_file_logging = true;

	m_file = std::fopen(file.c_str(), "w");
}

void Logger::DisableFileLogging()
{
	m_file_logging = false;
	if(!m_filename.empty()) std::fclose(m_file);
}

void Logger::SetConsoleLogging(bool on) { m_console_logging = on; }

void Logger::SetLevel(LogLevel target) { m_level = target; }

LogLevel Logger::GetLevel() const { return m_level; }

void Logger::SetLevelPreamble(bool on) { m_preamble_level = on; }

void Logger::SetFuncPreamble(bool on) { m_preamble_func = on; }

void Logger::SetFilePreamble(bool on) { m_preamble_file = on; }

void Logger::SetLinePreamble(bool on) { m_preamble_line = on; }

bool Logger::IsLevelDisabled(const LogLevel level)
{
	return (m_level == LogLevel::None || level < m_level ||
	        level <= LogLevel::Max || level >= LogLevel::None);
}

// TODO: remove this and use path type

const char* Logger::GetBaseName(const char* path)
{
	const char* filename = std::strrchr(path, '/');
	if(!filename)
		return std::strrchr(path, '\\') + 1;
	else
		return ++filename;
}
}  // namespace yz
