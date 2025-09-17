module;

#include <Windows.h>

module Spiky.Internal;

import :Logging;

namespace Spiky::Internal
{
	Graphics::StartupTask::Continuation InitCOMStartupTask::Setup()
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