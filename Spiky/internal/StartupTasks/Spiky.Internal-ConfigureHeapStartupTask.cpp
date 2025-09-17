// Project Name : Spiky
// File Name    : Spiky.Internal-ConfigureHeapStartupTask.cpp
// Author       : Felix Busch
// Created Date : 2025/09/17

module;

#include <Windows.h>
#include <format>

module Spiky.Internal;

import :Logging;

namespace Spiky::Internal
{
	Startup::StartupTask::Continuation ConfigureHeapStartupTask::Setup()
	{
		if (not HeapSetInformation(nullptr, HeapEnableTerminationOnCorruption, nullptr, 0))
		{
			Warning(std::format("HeapSetInformation failed with error code {}", GetLastError()));
		} else
		{
			Info("HeapSetInformation succeeded");
		}

		return Continue;
	}

	void ConfigureHeapStartupTask::Teardown()
	{
		Info("Uninitializing HeapSetInformation");
	}

}