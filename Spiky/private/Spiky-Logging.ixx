// Project Name : Spiky
// File Name    : Spiky-Logging.ixx
// Author       : Felix Busch
// Created Date : 2025/09/16

module;

#include <string>
#include <chrono>
//#include <stacktrace>

export module Spiky:Logging;

import Logging;

namespace Spiky
{
	void Log(
		LogLevel level,
		const std::string& message,
		const std::chrono::system_clock::time_point& time = std::chrono::system_clock::now()//,
		//const std::stacktrace& stacktrace = std::stacktrace::current()
	);

	void Trace(
		const std::string& message,
		const std::chrono::system_clock::time_point& time = std::chrono::system_clock::now()//,
		//const std::stacktrace& stacktrace = std::stacktrace::current()
	);

	void Debug(
		const std::string& message,
		const std::chrono::system_clock::time_point& time = std::chrono::system_clock::now()//,
		//const std::stacktrace& stacktrace = std::stacktrace::current()
	);

	void Info(
		const std::string& message,
		const std::chrono::system_clock::time_point& time = std::chrono::system_clock::now()//,
		//const std::stacktrace& stacktrace = std::stacktrace::current()
	);

	void Warning(
		const std::string& message,
		const std::chrono::system_clock::time_point& time = std::chrono::system_clock::now()//,
		//const std::stacktrace& stacktrace = std::stacktrace::current()
	);

	void Error(
		const std::string& message,
		const std::chrono::system_clock::time_point& time = std::chrono::system_clock::now()//,
		//const std::stacktrace& stacktrace = std::stacktrace::current()
	);
}
