// Project Name : Spiky
// File Name    : InitCOMStartupTask.ixx
// Author       : Felix Busch
// Created Date : 2025/09/17

export module Spiky.Internal:InitCOMStartupTask;

import Graphics.Launch;

export namespace Spiky::Internal
{
	struct InitCOMStartupTask : Graphics::StartupTask
	{
		Continuation Setup() override;
		void Teardown() override;
	};
}