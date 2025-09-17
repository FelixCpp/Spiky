module;

#include <string_view>
#include <string>
#include <optional>

module Spiky;

namespace Spiky
{
	extern LibraryData s_Data;
	extern std::unique_ptr<System::MonitorProvider> s_MonitorProvider;

	void ShowWindow()
	{
		s_Data.Window->SetVisible(true);
	}

	void HideWindow()
	{
		s_Data.Window->SetVisible(false);
	}

	bool IsWindowVisible()
	{
		return s_Data.Window->IsVisible();
	}

	void SetWindowSize(const int width, const int height, const bool recenter)
	{
		s_Data.Window->SetSize(width, height);

		if (recenter)
		{
			const std::optional<System::Monitor> primaryMonitor = s_MonitorProvider->GetPrimaryMonitor();
			
			if (primaryMonitor.has_value())
			{
				const Math::IntBoundary& workArea = primaryMonitor->WorkArea;
				const int x = workArea.Left + (workArea.Width - width) / 2;
				const int y = workArea.Top + (workArea.Height - height) / 2;
				s_Data.Window->SetPosition(x, y);
			}
		}
	}

	Math::Uint2 GetWindowSize()
	{
		return s_Data.Window->GetSize();
	}

	void SetWindowPosition(const int x, const int y)
	{
		s_Data.Window->SetPosition(x, y);
	}

	Math::Int2 GetWindowPosition()
	{
		return s_Data.Window->GetPosition();
	}

	void SetWindowTitle(const std::string_view title)
	{
		s_Data.Window->SetTitle(title);
	}

	std::string GetWindowTitle()
	{
		return s_Data.Window->GetTitle();
	}
}