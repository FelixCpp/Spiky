module;

#include <memory>

export module System.Monitor:MonitorProviderCache;

import :MonitorProvider;

namespace System
{
	export class MonitorProviderCache : public MonitorProvider
	{
	public:

		explicit MonitorProviderCache(std::unique_ptr<MonitorProvider> provider);

		[[nodiscard]] std::optional<Monitor> GetPrimaryMonitor() const override;
		[[nodiscard]] std::vector<Monitor> GetAvailableMonitors() const override;

		void Reset();
		void Reset(std::unique_ptr<MonitorProvider> provider);

	private:

		std::unique_ptr<MonitorProvider> m_Provider;
		mutable std::optional<Monitor> m_PrimaryMonitor;
		mutable std::vector<Monitor> m_AvailableMonitors;

	};
}
