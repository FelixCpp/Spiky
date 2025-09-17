module;

#include <memory>

#include <Windows.h>

module System.DPI;

namespace System
{
	ShCoreDPIService::ShCoreDPIService(const Context context) :
		m_Context(context)
	{
	}

	bool ShCoreDPIService::Enable()
	{
		const std::unique_ptr<HINSTANCE__, decltype(&FreeLibrary)> shcore(LoadLibraryW(L"Shcore.dll"), FreeLibrary);
		if (shcore == nullptr)
		{
			return false;
		}

		const auto setProcessDpiAwareness = reinterpret_cast<HRESULT(WINAPI*)(Context)>(GetProcAddress(shcore.get(), "SetProcessDpiAwareness"));
		if (setProcessDpiAwareness == nullptr)
		{
			return false;
		}

		const HRESULT result = setProcessDpiAwareness(m_Context);

		// We check exclusively for E_INVALIDARG since E_ACCESSDENIED means the DPI awareness is already set and cannot be changed.
		return result != E_INVALIDARG;
	}
}