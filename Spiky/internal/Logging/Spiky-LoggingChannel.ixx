// Project Name : Spiky
// File Name    : Spiky-LoggingChannel.ixx
// Author       : Felix Busch
// Created Date : 2025/09/17

module;

#include <memory>
#include <string>
#include <chrono>

export module Spiky:LoggingChannel;

import Logging;

import :LoggingStartupTask;

namespace Spiky
{
	class LoggingChannel
	{
	public:

		explicit LoggingChannel(std::unique_ptr<Logger> logger);
		void Submit(LogLevel level, const std::string& message, const std::chrono::system_clock::time_point& timestamp);
		const std::shared_ptr<LoggingStartupTask>& GetStartupTask() const;

	private:

		std::shared_ptr<LoggingStartupTask> m_LoggingTask;

	};
}
