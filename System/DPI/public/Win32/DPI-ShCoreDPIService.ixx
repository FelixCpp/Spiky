export module System.DPI:ShCoreDPIService;

import :DPIService;

namespace System
{
	export class ShCoreDPIService : public DPIService
	{
	public:

		enum class Context
		{
			Unaware = 0,
			SystemAware = 1,
			PerMonitorAware = 2,
		};

		explicit ShCoreDPIService(Context context);
		bool Enable() override;

	private:

		Context m_Context;
	};
}