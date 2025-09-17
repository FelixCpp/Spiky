// Project Name : Spiky
// File Name    : Spiky-MonitorProviderCache.ixx
// Author       : Felix Busch
// Created Date : 2025/09/17

module;

#include <optional>
#include <vector>
#include <memory>

export module Spiky:MonitorProviderCache;

import System.Monitor;

export namespace Spiky
{
	class MonitorProviderCache final : public System::MonitorProvider
	{
	public:

		explicit MonitorProviderCache(std::shared_ptr<MonitorProvider> provider);

		[[nodiscard]] std::optional<System::Monitor> GetPrimaryMonitor() const override;
		[[nodiscard]] std::vector<System::Monitor> GetAvailableMonitors() const override;

		void Clear();
		void Reset(std::shared_ptr<MonitorProvider> provider);

	private:

		std::shared_ptr<MonitorProvider> m_MonitorProvider;
		mutable std::optional<System::Monitor> m_PrimaryMonitor;
		mutable std::vector<System::Monitor> m_AvailableMonitors;

	};
}