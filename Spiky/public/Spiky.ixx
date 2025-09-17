module;

#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <chrono>

export module Spiky;

/// Export the window event to the user
export import :WindowEvent;

/// Export math utilities since it is used quite often
/// in graphics programming.
export import Math;

import Logging;

/// <summary>
/// Sketch interface to be implemented by the user
/// </summary>
export namespace Spiky
{
	struct Sketch
	{
		virtual ~Sketch() = default;
		virtual bool Setup() = 0;
		virtual void Event(const WindowEvent& event) = 0;
		virtual void Draw() = 0;
		virtual void Destroy() = 0;
	};

	int Launch(const std::function<std::unique_ptr<Sketch>()>& factory);
}

/// <summary>
/// Logging functionality.
/// </summary>
export namespace Spiky
{
	void Log(LogLevel level, const std::string& message, const std::chrono::system_clock::time_point& time = std::chrono::system_clock::now());
	void Trace(const std::string& message, const std::chrono::system_clock::time_point& time = std::chrono::system_clock::now());
	void Debug(const std::string& message, const std::chrono::system_clock::time_point& time = std::chrono::system_clock::now());
	void Info(const std::string& message, const std::chrono::system_clock::time_point& time = std::chrono::system_clock::now());
	void Warning(const std::string& message, const std::chrono::system_clock::time_point& time = std::chrono::system_clock::now());
	void Error(const std::string& message, const std::chrono::system_clock::time_point& time = std::chrono::system_clock::now());
}

/// <summary>
/// Windowing and event handling
/// </summary>
export namespace Spiky
{
	void ShowWindow();												  //!< Make the window visible to the user
	void HideWindow();												  //!< Hide the window from the user
	bool IsWindowVisible();											  //!< Get whether the window is currently visible to the user
	void SetWindowSize(int width, int height, bool recenter = true);  //!< Set the window size, optionally recentering it after resize on the primary monitor
	Math::Uint2 GetWindowSize();									  //!< Get the size of the content-area of the window
	void SetWindowPosition(int x, int y);							  //!< Set the window position in screen coordinates
	Math::Int2 GetWindowPosition();									  //!< Get the window position in screen coordinates
	void SetWindowTitle(std::string_view title);					  //!< Set the window title
	std::string GetWindowTitle();									  //!< Get the window title
}

//////////////////////////////// - Non-API - //////////////////////////////
///																		///
///	This Section contains type definitions and implementations that are	///
///	not part of the public API of the library.							///
///																		///
///////////////////////////////////////////////////////////////////////////

import :MonitorProviderCache;
import :ConfigureDPIStartupTask;
import :ConfigureHeapStartupTask;
import :InitCOMStartupTask;
import :LoggingStartupTask;
import :WindowStartupTask;
import :LoggingChannel;
import :Preconditions;
import :Window;

struct SpikyLibrary
{
	std::unique_ptr<Spiky::Window>				Window;				//!< The Core window of the sketch
	std::unique_ptr<Spiky::Sketch>				Sketch;				//!< The sketch provided by the user
	std::unique_ptr<Spiky::LoggingChannel>		LoggingChannel;		//!< The logging channel to use
	std::shared_ptr<System::MonitorProvider>	MonitorProvider;	//!< The monitor provider to use
};

module :private;

inline SpikyLibrary Library;