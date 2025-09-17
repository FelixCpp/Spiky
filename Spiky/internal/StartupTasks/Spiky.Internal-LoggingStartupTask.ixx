// Project Name : Spiky
// File Name    : Spiky.Internal-LoggingStartupTask.ixx
// Author       : Felix Busch
// Created Date : 2025/09/17

module;

#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

export module Spiky.Internal:LoggingStartupTask;

import Startup;

import :Logging;

export namespace Spiky::Internal
{
	class LoggingStartupTask : public Startup::StartupTask
	{
	public:

		struct LogEntry
		{
			LogLevel Level;
			std::string Message;
			std::chrono::system_clock::time_point Timestamp;
			//std::stacktrace Stacktrace;
		};

	public:

		void Submit(const LogEntry& entry);
		Continuation Setup() override;
		void Teardown() override;

	private:

		std::jthread m_LoggingThread;
		std::mutex m_SubmitMutex;
		std::condition_variable m_SubmitCondition;

		std::queue<LogEntry> m_SubmittedEntries;

	};
}