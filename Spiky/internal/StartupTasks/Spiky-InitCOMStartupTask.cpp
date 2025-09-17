// Project Name : Spiky
// File Name    : Spiky-InitCOMStartupTask.cpp
// Author       : Felix Busch
// Created Date : 2025/09/17

module;

#include <Windows.h>

module Spiky;

namespace Spiky
{
	Startup::StartupTask::Continuation InitCOMStartupTask::Setup()
	{
		if (FAILED(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE)))
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