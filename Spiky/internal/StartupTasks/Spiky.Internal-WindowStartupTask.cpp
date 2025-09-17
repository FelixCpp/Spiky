module;

#include <memory>
#include <optional>
#include <format>

module Spiky.Internal;

import System.Monitor;

import :Logging;

namespace Spiky::Internal
{
	WindowStartupTask::WindowStartupTask(
		std::shared_ptr<Window>& window,
		std::shared_ptr<System::MonitorProvider> monitorProvider
	): m_Window(window), m_MonitorProvider(std::move(monitorProvider))
	{
	}

	Startup::StartupTask::Continuation WindowStartupTask::Setup()
	{
		int windowLeft = 100, windowTop = 100;

		constexpr int windowWidth = 1280;
		constexpr int windowHeight = 720;
		m_MonitorProvider->GetAvailableMonitors();

		// Try to center the window on the primary monitor on startup
		if (const auto primaryMonitor = m_MonitorProvider->GetPrimaryMonitor())
		{
			windowLeft = primaryMonitor->WorkArea.Left + (primaryMonitor->WorkArea.Width - windowWidth) / 2;
			windowTop = primaryMonitor->WorkArea.Top + (primaryMonitor->WorkArea.Height - windowHeight) / 2;
			Info(std::format("Initial Window Position: {}, {}", windowLeft, windowTop));
		}

		m_Window = std::make_shared<Window>(windowLeft, windowTop, windowWidth, windowHeight, "Spiky Application");
		Info("Window created successfully");
		return Continue;
	}

	void WindowStartupTask::Teardown()
	{
		Info("Destroying Window");
		m_Window.reset();
	}
}