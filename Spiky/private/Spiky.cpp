module;

#include <memory>
#include <thread>

module Spiky;

import System.DPI;
import System.Monitor;

import Startup;

using namespace System;

namespace Spiky
{
	LibraryData s_Data;
	std::unique_ptr<MonitorProvider> s_MonitorProvider = std::make_unique<MonitorProviderCache>(std::make_unique<Win32MonitorProvider>());
	std::shared_ptr<Internal::LoggingStartupTask> s_LoggingTask = std::make_shared<Internal::LoggingStartupTask>();

	int Launch(const std::function<std::unique_ptr<Sketch>()>& factory)
	{
		Startup::AppStartup startup;
		startup.AddStartupTask(s_LoggingTask);
		startup.AddStartupTask(std::make_shared<Internal::ConfigureHeapStartupTask>());
		startup.AddStartupTask(std::make_shared<Internal::InitCOMStartupTask>());

		startup.Run([]
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
		});

		return 0;
	}
}