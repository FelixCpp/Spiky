// Project Name : Spiky
// File Name    : Spiky.Internal-InitCOMStartupTask.ixx
// Author       : Felix Busch
// Created Date : 2025/09/17

export module Spiky.Internal:InitCOMStartupTask;

import Startup;

export namespace Spiky::Internal
{
	struct InitCOMStartupTask : Startup::StartupTask
	{
		Continuation Setup() override;
		void Teardown() override;
	};
}