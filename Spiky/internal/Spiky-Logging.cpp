module;

#include <memory>
#include <string>
#include <chrono>

module Spiky.Internal;

namespace Spiky
{
	extern std::shared_ptr<Internal::LoggingStartupTask> s_LoggingTask;

	void Log(const LogLevel level, const std::string& message, const std::chrono::system_clock::time_point& time/*, const std::stacktrace& stacktrace*/)
	{
		s_LoggingTask->Submit({
			.Level = level,
			.Message = message,
			.Timestamp = time,
		});
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