// Project Name : Spiky
// File Name    : Spiky-ConfigureHeapStartupTask.ixx
// Author       : Felix Busch
// Created Date : 2025/09/17

export module Spiky:ConfigureHeapStartupTask;

import Startup;

export namespace Spiky
{
	struct ConfigureHeapStartupTask : Startup::StartupTask
	{
		Continuation Setup() override;
		void Teardown() override;
	};
}