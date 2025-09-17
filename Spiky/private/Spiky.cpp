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
	std::shared_ptr<MonitorProvider> s_MonitorProvider = std::make_unique<MonitorProviderCache>(std::make_unique<Win32MonitorProvider>());
	auto s_LoggingTask = std::make_shared<Internal::LoggingStartupTask>();

	int Launch(const std::function<std::unique_ptr<Sketch>()>& factory)
	{
		Startup::AppStartup startup;
		startup.AddStartupTask(s_LoggingTask);
		startup.AddStartupTask(std::make_shared<Internal::ConfigureHeapStartupTask>());
		startup.AddStartupTask(std::make_shared<Internal::InitCOMStartupTask>());
		startup.AddStartupTask(std::make_shared<Internal::WindowStartupTask>(s_Data.Window, s_MonitorProvider));

		startup.Run([&]
		{
			s_Data.Window->SetVisible(true);

			bool running = true;
			while (running)
			{
				s_Data.Window->HandleEvents(
					[&running](const WindowEvent::Closed&) { running = false; }
				);
			}
		});

		return 0;
	}
}