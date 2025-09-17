export module System.DPI:DPIService;

namespace System
{
	export struct DPIService
	{
		virtual ~DPIService() = default;
		virtual bool Enable() = 0;
	};
}