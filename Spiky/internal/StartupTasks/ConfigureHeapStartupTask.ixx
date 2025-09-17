// Project Name : Spiky
// File Name    : ConfigureHeapStartupTask.ixx
// Author       : Felix Busch
// Created Date : 2025/09/17

export module Spiky.Internal:ConfigureHeapStartupTask;

import Graphics.Launch;

export namespace Spiky::Internal
{
	struct ConfigureHeapStartupTask : Graphics::StartupTask
	{
		Continuation Setup() override;
		void Teardown() override;
	};
}