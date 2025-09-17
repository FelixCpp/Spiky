module;

#include <memory>

module Spiky;

import System.DPI;
import System.Monitor;

using namespace System;

namespace Spiky
{
	LibraryData s_Data;
	std::unique_ptr<MonitorProvider> s_MonitorProvider = std::make_unique<MonitorProviderCache>(std::make_unique<Win32MonitorProvider>());

	int Launch(const std::function<std::unique_ptr<Sketch>()>& factory)
	{
		const auto isEnabled = Enable(
			User32DPIService(User32DPIService::Context::PerMonitorAwareV2),
			ShCoreDPIService(ShCoreDPIService::Context::PerMonitorAware)
		);

		if (not isEnabled)
		{
			Warning("Failed to set DPI Awareness");
		}

		s_Data.Window = std::make_unique<Window>(1280, 720, "Spiky App");
		auto& window = *s_Data.Window;

		s_Data.Sketch = factory();
		const auto& sketch = s_Data.Sketch;

		if (sketch == nullptr or not sketch->Setup())
		{
			Error("Failed to setup sketch");
			return -1;
		}

		window.SetVisible(true);

		bool running = true;
		while (running)
		{
			window.HandleEvents(
				[&running](const WindowEvent::Closed&)
				{
					Debug("Window closed");
					running = false;
				}
			);

			sketch->Draw();
		}

		sketch->Destroy();

		return 0;
	}
}