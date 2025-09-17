module;

#include <memory>
#include <string>
#include <chrono>

module Spiky.Internal;

namespace Spiky
{
	/*Logger s_Logger(
		std::make_unique<DevelopmentLogFilter>(),
		std::make_unique<FmtLogPrinter>(),
		std::make_unique<ConsoleLogOutput>()
	);*/

	extern std::shared_ptr<Internal::LoggingStartupTask> s_LoggingTask;

	void Log(const LogLevel level, const std::string& message, const std::chrono::system_clock::time_point& time/*, const std::stacktrace& stacktrace*/)
	{
		s_LoggingTask->Submit({
			.Level = level,
			.Message = message,
			.Timestamp = time,
		});
		//s_Logger.Log(level, message, time/*, stacktrace*/);
	}

	void Trace(const std::string& message, const std::chrono::system_clock::time_point& time/*, const std::stacktrace& stacktrace*/)
	{
		Log(LogLevel::Trace, message, time/*, stacktrace*/);
	}

	void Debug(const std::string& message, const std::chrono::system_clock::time_point& time/*, const std::stacktrace& stacktrace*/)
	{
		Log(LogLevel::Debug, message, time/*, stacktrace*/);
	}

	void Info(const std::string& message, const std::chrono::system_clock::time_point& time/*, const std::stacktrace& stacktrace*/)
	{
		Log(LogLevel::Info, message, time/*, stacktrace*/);
	}

	void Warning(const std::string& message, const std::chrono::system_clock::time_point& time/*, const std::stacktrace& stacktrace*/)
	{
		Log(LogLevel::Warning, message, time/*, stacktrace*/);
	}

	void Error(const std::string& message, const std::chrono::system_clock::time_point& time/*, const std::stacktrace& stacktrace*/)
	{
		Log(LogLevel::Error, message, time/*, stacktrace*/);
	}
}