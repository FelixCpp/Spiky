module;

#include <memory>
#include <string>
#include <string_view>

#include <d2d1.h>

module Spiky;

import System.Monitor;

import Startup;

using namespace System;

/// <summary>
/// Sketch interface to be implemented by the user
/// </summary>
namespace Spiky
{
	int Launch(const std::function<std::unique_ptr<Sketch>()>& factory)
	{
		Library.LoggingChannel = std::make_unique<LoggingChannel>(std::make_unique<Logger>(
			std::make_unique<DevelopmentLogFilter>(),
			std::make_unique<FmtLogPrinter>(),
			std::make_unique<ConsoleLogOutput>()
		));

		Library.MonitorProvider = std::make_shared<MonitorProviderCache>(std::make_shared<Win32MonitorProvider>());


		Startup::AppStartup startup;
		startup.AddStartupTask(Library.LoggingChannel->GetStartupTask());
		startup.AddStartupTask(std::make_shared<ConfigureHeapStartupTask>());
		startup.AddStartupTask(std::make_shared<InitCOMStartupTask>());
		startup.AddStartupTask(std::make_shared<ConfigureDPIStartupTask>());
		startup.AddStartupTask(std::make_shared<WindowStartupTask>(Library.Window, Library.MonitorProvider));

		DeviceResourcesScaler scaler(&Library.DeviceResources);
		startup.AddStartupTask(std::make_shared<ConfigureDeviceIndependentResourcesStartupTask>(&Library.IndependentResources));
		startup.AddStartupTask(std::make_shared<ConfigureDeviceResourcesStartupTask>(&Library.DeviceResources, &Library.IndependentResources, &scaler, [] { return Library.Window.get(); }));

		startup.Run([&]
		{
			Library.Window->SetVisible(true);

			Library.Sketch = factory();
			if (Library.Sketch == nullptr or not Library.Sketch->Setup())
			{
				Error("Couldn't setup the sketch");
				return;
			}

			bool running = true;
			while (running)
			{
				while (const auto event = Library.Window->PollEvent())
				{
					const bool forwardToUser = event->Visit(
						[&running](const WindowEvent::Closed&)
						{
							running = false;
							return true;
						},
						[&scaler](const WindowEvent::Resized& resized)
						{
							scaler.Resize(resized.Width, resized.Height);
							return true;
						},
						[](const auto&)
						{
							return true;
						}
					);

					if (forwardToUser)
					{
						Library.Sketch->Event(*event);
					}
				}

				Library.DeviceResources.D2DContext->BeginDraw();
				Library.Sketch->Draw();
				Library.DeviceResources.D2DContext->EndDraw();
				Library.DeviceResources.DXGISwapChain->Present(1, 0);
			}

			Library.Sketch->Destroy();
		});

		return 0;
	}
}

/// <summary>
/// Logging functionality
/// </summary>
namespace Spiky
{
	void Log(const LogLevel level, const std::string& message, const std::chrono::system_clock::time_point& time) { Library.LoggingChannel->Submit(level, message, time); }
	void Trace(const std::string& message, const std::chrono::system_clock::time_point& time) { Log(LogLevel::Trace, message, time); }
	void Debug(const std::string& message, const std::chrono::system_clock::time_point& time) { Log(LogLevel::Debug, message, time); }
	void Info(const std::string& message, const std::chrono::system_clock::time_point& time) { Log(LogLevel::Info, message, time); }
	void Warning(const std::string& message, const std::chrono::system_clock::time_point& time) { Log(LogLevel::Warning, message, time); }
	void Error(const std::string& message, const std::chrono::system_clock::time_point& time) { Log(LogLevel::Error, message, time); }
}

/// <summary>
/// Windowing and event handling
/// </summary>
namespace Spiky
{
	void ShowWindow() { Library.Window->SetVisible(true); }
	void HideWindow() { Library.Window->SetVisible(true); }
	bool IsWindowVisible() { return Library.Window->IsVisible(); }

	void SetWindowSize(const int width, const int height, const bool recenter)
	{
		Library.Window->SetSize(width, height);

		if (recenter)
		{
			if (const auto monitor = Library.MonitorProvider->GetPrimaryMonitor())
			{
				const int windowLeft = monitor->WorkArea.Left + (monitor->WorkArea.Width - width) / 2;
				const int windowTop = monitor->WorkArea.Top + (monitor->WorkArea.Height - height) / 2;
				SetWindowPosition(windowLeft, windowTop);
			}
		}
	}

	Math::Uint2 GetWindowSize()	{ return Library.Window->GetSize(); }
	void SetWindowPosition(const int x, const int y) { Library.Window->SetPosition(x, y); }
	Math::Int2 GetWindowPosition() { return Library.Window->GetPosition(); }
	void SetWindowTitle(const std::string_view title) { Library.Window->SetTitle(title); }
	std::string GetWindowTitle() { return Library.Window->GetTitle(); }
}

/// <summary>
/// Graphics and rendering
/// </summary>
namespace Spiky
{
	void Background(const int32_t red, const int32_t green, const int32_t blue, const int32_t alpha)
	{
		const float r = static_cast<float>(red) / 255.0f;
		const float g = static_cast<float>(green) / 255.0f;
		const float b = static_cast<float>(blue) / 255.0f;
		const float a = static_cast<float>(alpha) / 255.0f;
		Library.DeviceResources.D2DContext->Clear(D2D1::ColorF(r, g, b, a));
	}
}
