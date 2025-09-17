export module System.DPI:User32DPIService;

import :DPIService;

namespace System
{
	export class User32DPIService : public DPIService
	{
	public:

		enum class Context
		{
			Unaware,
			SystemAware,
			PerMonitorAware,
			PerMonitorAwareV2,
		};

		explicit User32DPIService(Context context);
		bool Enable() override;

	private:

		Context m_Context;

	};
}