// Project Name : Spiky
// File Name    : Spiky.Internal-ConfigureHeapStartupTask.ixx
// Author       : Felix Busch
// Created Date : 2025/09/17

export module Spiky.Internal:ConfigureHeapStartupTask;

import Startup;

export namespace Spiky::Internal
{
	struct ConfigureHeapStartupTask : Startup::StartupTask
	{
		Continuation Setup() override;
		void Teardown() override;
	};
}