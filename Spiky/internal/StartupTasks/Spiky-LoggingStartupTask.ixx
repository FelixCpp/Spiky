// Project Name : Spiky
// File Name    : Spiky-LoggingStartupTask.ixx
// Author       : Felix Busch
// Created Date : 2025/09/17

module;

#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>

export module Spiky:LoggingStartupTask;

import Startup;
import Logging;

namespace Spiky
{
	class LoggingStartupTask : public Startup::StartupTask
	{
	public:

		struct LogEntry
		{
			LogLevel Level;
			std::string Message;
			std::chrono::system_clock::time_point Timestamp;
		};

	public:

		explicit LoggingStartupTask(std::unique_ptr<Logger> logger);
		void Submit(const LogEntry& entry);
		Continuation Setup() override;
		void Teardown() override;

	private:

		std::jthread m_LoggingThread;
		std::mutex m_SubmitMutex;
		std::condition_variable m_SubmitCondition;

		std::queue<LogEntry> m_SubmittedEntries;
		std::unique_ptr<Logger> m_Logger;

	};
}