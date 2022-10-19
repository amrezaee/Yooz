#include <Core/yzLogger.hpp>

#include <loguru/loguru.cpp>

#include <Platform/yzMessageBox.hpp>

namespace yz
{
void Logger::Init(int argc, char** argv)
{
	loguru::g_preamble_date    = false;
	loguru::g_preamble_time    = false;
	loguru::g_preamble_thread  = false;
	loguru::g_preamble_verbose = false;
	loguru::g_stderr_verbosity = loguru::Verbosity_1;

	loguru::init(argc, argv);

	loguru::set_fatal_handler(
	        [](const loguru::Message& message)
	        {
		        MessageBoxFatal(message.message);
	        });
}

void Logger::SetVerbosity(Verbosity v)
{
	loguru::g_stderr_verbosity = static_cast<int>(v);
}

void Logger::SetFilePreamble(bool enable)
{
	loguru::g_preamble_file = enable;
}
void Logger::SetVerbosityPreamble(bool enable)
{
	loguru::g_preamble_verbose = enable;
}
}  // namespace yz
