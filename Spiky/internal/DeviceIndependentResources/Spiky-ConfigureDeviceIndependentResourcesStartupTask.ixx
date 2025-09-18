// Project Name : Spiky
// File Name    : Spiky-ConfigureDeviceIndependentResourcesStartupTask.ixx
// Author       : Felix Busch
// Created Date : 2025/09/18

export module Spiky:ConfigureDeviceIndependentResourcesStartupTask;

import Startup;

import :DeviceIndependentResources;

namespace Spiky
{
	class ConfigureDeviceIndependentResourcesStartupTask : public Startup::StartupTask
	{
	public:

		explicit ConfigureDeviceIndependentResourcesStartupTask(DeviceIndependentResources* resources);

		Continuation Setup() override;
		void Teardown() override;

	private:

		DeviceIndependentResources* m_Resources;

	};
}
