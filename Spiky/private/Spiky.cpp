module;

#include <memory>
#include <vector>

module Spiky;

import System.DPI;
import System.Monitor;

import Graphics.Launch;

using namespace System;

namespace Spiky
{
	LibraryData s_Data;
	std::unique_ptr<MonitorProvider> s_MonitorProvider = std::make_unique<MonitorProviderCache>(std::make_unique<Win32MonitorProvider>());

	int Launch(const std::function<std::unique_ptr<Sketch>()>& factory)
	{
		Graphics::AppStartup startup;
		startup.AddStartupTask(std::make_unique<Internal::ConfigureHeapStartupTask>());
		startup.AddStartupTask(std::make_unique<Internal::InitCOMStartupTask>());

		startup.Run([]
		{
			
		});

		return 0;
	}
}