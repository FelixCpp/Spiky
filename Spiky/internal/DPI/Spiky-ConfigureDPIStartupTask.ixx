// Project Name : Spiky
// File Name    : Spiky-ConfigureDPIStartupTask.ixx
// Author       : Felix Busch
// Created Date : 2025/09/18

export module Spiky:ConfigureDPIStartupTask;

import Startup;

namespace Spiky
{
	struct ConfigureDPIStartupTask : Startup::StartupTask
	{
		Continuation Setup() override;
		void Teardown() override;
	};
}