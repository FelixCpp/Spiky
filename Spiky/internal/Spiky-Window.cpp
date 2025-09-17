module;

#include <Windows.h>

#include <string>
#include <optional>
#include <memory>

module Spiky.Internal;

import System.Monitor;

namespace Spiky
{
	extern std::unique_ptr<System::MonitorProvider> s_MonitorProvider;

	[[nodiscard]] std::wstring StringToWide(const std::string_view source)
	{
		const int requiredLength = MultiByteToWideChar(CP_UTF8, 0, source.data(), static_cast<int>(source.length()), nullptr, 0);
		Expect(requiredLength > 0, [] { return "Couldn't convert string to wide string."; });

		std::wstring wideString(requiredLength, L'\0');
		const int convertedLength = MultiByteToWideChar(CP_UTF8, 0, source.data(), static_cast<int>(source.length()), wideString.data(), requiredLength);
		Expect(convertedLength == requiredLength, [] { return "Couldn't convert string to wide string."; });

		return wideString;
	}

	[[nodiscard]] std::string WideToString(const std::wstring_view source)
	{
		const int requiredLength = WideCharToMultiByte(CP_UTF8, 0, source.data(), static_cast<int>(source.length()), nullptr, 0, nullptr, nullptr);
		Expect(requiredLength > 0, [] { return "Couldn't convert wide string to string."; });

		std::string string(requiredLength, '\0');
		const int convertedLength = WideCharToMultiByte(CP_UTF8, 0, source.data(), static_cast<int>(source.length()), string.data(), requiredLength, nullptr, nullptr);
		Expect(convertedLength == requiredLength, [] { return "Couldn't convert wide string to string."; });

		return string;
	}

	Window::Window(const int width, const int height, const std::string_view title)
	{
		constexpr DWORD dwStyle = WS_OVERLAPPEDWINDOW;
		constexpr DWORD dwExStyle = WS_EX_OVERLAPPEDWINDOW;

		RECT windowArea = { .left = 0l, .top = 0l, .right = static_cast<LONG>(width), .bottom = static_cast<LONG>(height) };
		Expect(
			AdjustWindowRectEx(&windowArea, dwStyle, FALSE, dwExStyle),
			[] { return "Couldn't adjust window rectangle."; }
		);

		const int windowWidth = static_cast<int>(windowArea.right - windowArea.left);
		const int windowHeight = static_cast<int>(windowArea.bottom - windowArea.top);

		const Math::Int2 windowPosition = [windowWidth, windowHeight] -> Math::Int2
		{
			const std::optional<System::Monitor> monitor = s_MonitorProvider->GetPrimaryMonitor();

			if (not monitor.has_value())
			{
				return { CW_USEDEFAULT, CW_USEDEFAULT };
			}

			const int32_t windowLeft = monitor->WorkArea.Left + (monitor->WorkArea.Width - windowWidth) / 2;
			const int32_t windowTop = monitor->WorkArea.Top + (monitor->WorkArea.Height - windowHeight) / 2;

			return { windowLeft, windowTop };
		}();
						
		const HMONITOR monitor = CheckNotNull(
			MonitorFromPoint({}, MONITOR_DEFAULTTONEAREST),
			[] { return "Couldn't retrieve handle to the primary monitor."; }
		);

		MONITORINFO monitorInfo = {.cbSize = sizeof(MONITORINFO)};
		Expect(
			GetMonitorInfoW(monitor, &monitorInfo), 
			[] { return "Couldn't retrieve information about the primary monitor."; }
		);

		const WNDCLASSEXW wcex = {
			.cbSize = sizeof(WNDCLASSEX),
			.style = CS_HREDRAW | CS_VREDRAW,
			.lpfnWndProc = &WndProc,
			.cbClsExtra = 0,
			.cbWndExtra = 0,
			.hInstance = GetModuleHandle(nullptr),
			.hIcon = LoadIcon(nullptr, IDI_APPLICATION),
			.hCursor = LoadCursor(nullptr, IDC_ARROW),
			.hbrBackground = nullptr,
			.lpszMenuName = nullptr,
			.lpszClassName = TEXT("SpikyWindowClass"),
			.hIconSm = LoadIcon(nullptr, IDI_APPLICATION)
		};

		Expect(RegisterClassEx(&wcex), [] { return "Couldn't register window class."; });

		m_WindowHandle = CheckNotNull(
			CreateWindowExW(dwExStyle, wcex.lpszClassName, StringToWide(title).c_str(), dwStyle, windowPosition.X, windowPosition.Y, windowWidth, windowHeight, nullptr, nullptr, wcex.hInstance, this),
			[] { return "Couldn't create window."; }
		);
	}

	Window::~Window()
	{
		DestroyWindow(m_WindowHandle);
	}

	void Window::SetVisible(const bool visible)
	{
		ShowWindow(m_WindowHandle, visible ? SW_SHOW : SW_HIDE);
	}

	bool Window::IsVisible() const
	{
		return IsWindowVisible(m_WindowHandle) != FALSE;
	}

	void Window::SetSize(const int width, const int height)
	{
		const DWORD dwStyle = GetWindowLongW(m_WindowHandle, GWL_STYLE);
		const DWORD dwExStyle = GetWindowLongW(m_WindowHandle, GWL_EXSTYLE);

		RECT windowArea = { .left = 0l, .top = 0l, .right = static_cast<LONG>(width), .bottom = static_cast<LONG>(height) };
		Expect(
			AdjustWindowRectEx(&windowArea, dwStyle, FALSE, dwExStyle),
			[] { return "Couldn't adjust window rectangle."; }
		);

		const int windowWidth = static_cast<int>(windowArea.right - windowArea.left);
		const int windowHeight = static_cast<int>(windowArea.bottom - windowArea.top);

		SetWindowPos(m_WindowHandle, nullptr, 0, 0, windowWidth, windowHeight, SWP_NOMOVE | SWP_NOZORDER);
	}

	Math::Uint2 Window::GetSize() const
	{
		RECT windowArea = {};
		Expect(
			GetClientRect(m_WindowHandle, &windowArea),
			[] { return "Couldn't retrieve window size"; }
		);

		const uint32_t width = static_cast<uint32_t>(windowArea.right - windowArea.left);
		const uint32_t height = static_cast<uint32_t>(windowArea.bottom - windowArea.top);
		return { width, height };
	}


	void Window::SetPosition(const int x, const int y)
	{
		SetWindowPos(m_WindowHandle, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}

	Math::Int2 Window::GetPosition() const
	{
		RECT windowBoundary = {};
		Expect(
			GetWindowRect(m_WindowHandle, &windowBoundary),
			[] { return "Couldn't retrieve window position."; }
		);

		const auto x = static_cast<int32_t>(windowBoundary.left);
		const auto y = static_cast<int32_t>(windowBoundary.top);
		return { x, y };
	}

	void Window::SetTitle(const std::string_view title)
	{
		SetWindowTextW(m_WindowHandle, StringToWide(title).c_str());
	}

	std::string Window::GetTitle() const
	{
		const int length = GetWindowTextLengthW(m_WindowHandle);
		Expect(length >= 0, [] { return "Couldn't retrieve window title length."; });

		std::wstring wideTitle(length, L'\0');
		const int retrievedLength = GetWindowTextW(m_WindowHandle, wideTitle.data(), length + 1);
		Expect(retrievedLength == length, [] { return "Couldn't retrieve window title."; });

		return WideToString(wideTitle);
	}

	HWND Window::GetNativeHandle() const
	{
		return m_WindowHandle;
	}

	std::optional<WindowEvent> Window::PollEvent()
	{
		if (m_EventQueue.empty())
		{
			QueueEvents();
		}

		if (not m_EventQueue.empty())
		{
			WindowEvent event = std::move(m_EventQueue.front());
			m_EventQueue.pop();
			return event;
		}

		return std::nullopt;
	}


	LRESULT Window::WndProc(const HWND hWnd, const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
	{
		if (uMsg == WM_CREATE)
		{
			SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(reinterpret_cast<LPCREATESTRUCTW>(lParam)->lpCreateParams));
			return 1;
		}

		if (const auto window = reinterpret_cast<Window*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA)))
		{
			window->HandleMessage(uMsg, wParam, lParam);
		}

		return DefWindowProcW(hWnd, uMsg, wParam, lParam);
	}

	void Window::HandleMessage(const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
	{
		switch (uMsg)
		{
			case WM_CLOSE:
			{
				m_EventQueue.emplace(WindowEvent::Closed{});
			} break;

			default:
				break;
		}
	}

	void Window::QueueEvents() const
	{
		MSG msg = {};
		while (PeekMessageW(&msg, m_WindowHandle, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}

}
