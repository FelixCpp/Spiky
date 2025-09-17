module;

#include <optional>
#include <Windows.h>
#include <bit>
#include <vector>

module System.Monitor;

namespace System
{
	constexpr Math::IntBoundary RectToBoundary(const RECT& rect)
	{
		return Math::IntBoundary::FromLTRB(
			static_cast<int32_t>(rect.left),
			static_cast<int32_t>(rect.top),
			static_cast<int32_t>(rect.right),
			static_cast<int32_t>(rect.bottom)
		);
	}

	std::optional<Monitor> Win32MonitorProvider::GetPrimaryMonitor() const
	{
		const HWND desktopWindow = GetDesktopWindow();
		if (desktopWindow == nullptr)
		{
			return std::nullopt;
		}

		const HMONITOR primaryMonitor = MonitorFromWindow(desktopWindow, MONITOR_DEFAULTTOPRIMARY);
		if (primaryMonitor == nullptr)
		{
			return std::nullopt;
		}

		MONITORINFOEXW monitorInfo = {};
		monitorInfo.cbSize = sizeof(MONITORINFOEXW);
		if (not GetMonitorInfoW(primaryMonitor, &monitorInfo))
		{
			return std::nullopt;
		}

		return Monitor{
			.Name = monitorInfo.szDevice,
			.WorkArea = RectToBoundary(monitorInfo.rcWork),
			.Area = RectToBoundary(monitorInfo.rcMonitor)
		};
	}

	std::vector<Monitor> Win32MonitorProvider::GetAvailableMonitors() const
	{
		std::vector<Monitor> result;

		EnumDisplayMonitors(
			nullptr,
			nullptr,
			[](const HMONITOR hMonitor, HDC, LPRECT, const LPARAM dwData) -> BOOL
			{
				auto* monitors = std::bit_cast<std::vector<Monitor>*>(dwData);

				MONITORINFOEXW monitorInfo = {};
				monitorInfo.cbSize = sizeof(MONITORINFOEXW);
				if (not GetMonitorInfoW(hMonitor, &monitorInfo))
				{
					return TRUE; // Continue enumeration
				}

				monitors->emplace_back(Monitor{
					.Name = monitorInfo.szDevice,
					.WorkArea = RectToBoundary(monitorInfo.rcWork),
					.Area = RectToBoundary(monitorInfo.rcMonitor)
				});

				return TRUE; // Continue enumeration
			},
			reinterpret_cast<LPARAM>(&result)
		);

		return result;
	}
}
