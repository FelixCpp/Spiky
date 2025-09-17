module;

#include <memory>

#include <Windows.h>

module System.DPI;

namespace System
{
	User32DPIService::User32DPIService(const Context context) :
		m_Context(context)
	{
	}

	bool User32DPIService::Enable()
	{
		const std::unique_ptr<HINSTANCE__, decltype(&FreeLibrary)> user32(LoadLibraryW(L"User32.dll"), FreeLibrary);
		if (user32 == nullptr)
		{
			return false;
		}

		const auto setProcessDpiAwarenessContext = reinterpret_cast<BOOL(WINAPI*)(DPI_AWARENESS_CONTEXT)>(GetProcAddress(user32.get(), "SetProcessDpiAwarenessContext"));
		if (setProcessDpiAwarenessContext == nullptr)
		{
			return false;
		}

		const auto ctx = [context = m_Context]
		{
			switch (context)
			{
				case Context::Unaware: return DPI_AWARENESS_CONTEXT_UNAWARE;
				case Context::SystemAware: return DPI_AWARENESS_CONTEXT_SYSTEM_AWARE;
				case Context::PerMonitorAware: return DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE;
				case Context::PerMonitorAwareV2: return DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2;
				default: return DPI_AWARENESS_CONTEXT_UNAWARE;
			}
		}();


		return setProcessDpiAwarenessContext(ctx) != FALSE;
	}
}