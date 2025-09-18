// Project Name : Spiky
// File Name    : Spiky-ConfigureDeviceIndependentResourcesStartupTask.ixx
// Author       : Felix Busch
// Created Date : 2025/09/18

module;

#include <functional>

export module Spiky:ConfigureDeviceResourcesStartupTask;

import Startup;

import :DeviceResources;
import :DeviceResourcesScaler;
import :DeviceIndependentResources;
import :Window;

namespace Spiky
{
	class ConfigureDeviceResourcesStartupTask : public Startup::StartupTask
	{
	public:

		explicit ConfigureDeviceResourcesStartupTask(
			DeviceResources* resources,
			DeviceIndependentResources* independentResources,
			DeviceResourcesScaler* scaler,
			const std::function<Window*()>& windowProvider
		);

		Continuation Setup() override;
		void Teardown() override;

	private:

		DeviceResources* m_Resources;
		DeviceIndependentResources* m_IndependentResources;
		DeviceResourcesScaler* m_ResourcesScaler;
		std::function<Window*()> m_WindowProvider;

	};
}
