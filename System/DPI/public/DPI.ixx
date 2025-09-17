module;

#include <concepts>

export module System.DPI;

export import :DPIService;

#ifdef PLATFORM_WINDOWS
export import :ShCoreDPIService;
export import :User32DPIService;
#endif

namespace System
{
	export template <std::derived_from<DPIService> ... Services>
	bool Enable(Services&& ... services)
	{
		return (services.Enable() or ...);
	}
}