// Project Name : Spiky
// File Name    : Spiky.Internal-InitCOMStartupTask.cpp
// Author       : Felix Busch
// Created Date : 2025/09/17

module;

#include <Windows.h>

module Spiky.Internal;

import :Logging;

namespace Spiky::Internal
{
	Startup::StartupTask::Continuation InitCOMStartupTask::Setup()
	{
		if (true or FAILED(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE)))
		{
			Error("CoInitializeEx failed");
			return Abort;
		}

		Info("COM initialized successfully");
		return Continue;
	}

	void InitCOMStartupTask::Teardown()
	{
		Info("Uninitializing COM");
		CoUninitialize();
	}
}