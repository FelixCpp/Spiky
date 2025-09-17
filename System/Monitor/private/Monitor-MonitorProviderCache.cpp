module;

#include <optional>

module System.Monitor;

namespace System
{
	MonitorProviderCache::MonitorProviderCache(std::unique_ptr<MonitorProvider> provider):
		m_Provider(std::move(provider))
	{
	}

	std::optional<Monitor> MonitorProviderCache::GetPrimaryMonitor() const
	{
		if (not m_PrimaryMonitor.has_value())
		{
			m_PrimaryMonitor = m_Provider->GetPrimaryMonitor();
		}

		return m_PrimaryMonitor;
	}

	std::vector<Monitor> MonitorProviderCache::GetAvailableMonitors() const
	{
		if (m_AvailableMonitors.empty())
		{
			m_AvailableMonitors = m_Provider->GetAvailableMonitors();
		}

		return m_AvailableMonitors;
	}

	void MonitorProviderCache::Reset()
	{
		m_PrimaryMonitor = std::nullopt;
		m_AvailableMonitors.clear();
	}

	void MonitorProviderCache::Reset(std::unique_ptr<MonitorProvider> provider)
	{
		m_Provider = std::move(provider);
		Reset();
	}
}