// Project Name : Logging
// File Name    : Logging-FmtLogPrinter.cpp
// Author       : Felix Busch
// Created Date : 2025/09/16

module;

#include <string>
#include <format>
#include <chrono>

module Logging;

[[nodiscard]] std::string LogLevelToString(const LogLevel level)
{
	switch (level)
	{
		using enum LogLevel;
		case Trace:   return "TRACE";
		case Debug: return "DEBUG";
		case Info: return "INFO";
		case Warning: return "WARNING";
		case Error: return "ERROR";
		default: return "UNKNOWN";
	}
}

[[nodiscard]] std::string GetColorForLogLevel(const LogLevel level)
{
	switch (level)
	{
		using enum LogLevel;
		case Trace:   return "\033[37m"; // White
		case Debug: return "\033[36m"; // Cyan
		case Info: return "\033[32m"; // Green
		case Warning: return "\033[33m"; // Yellow
		case Error: return "\033[31m"; // Red
		default: return "\033[0m"; // Reset
	}
}

inline static constexpr std::string_view RESET_COLOR = "\033[0m";

LogOutputEvent FmtLogPrinter::Print(const LogEvent& event)
{
	// The output should be formatted foloowing the fmt-style:
	// [TIMESTAMP] [LEVEL] MESSAGE

	const std::string timestamp = std::format("{:%d.%m.%Y %H:%M:%S}", std::chrono::floor<std::chrono::seconds>(event.Timestamp));
	const std::string level = LogLevelToString(event.Level);
	const std::string message = std::format("{}{}{}", GetColorForLogLevel(event.Level), event.Message, RESET_COLOR);

	return LogOutputEvent{
		.Lines = { std::format("[{}] [{}] {}", timestamp, level, message) },
		.Origin = event
	};
}