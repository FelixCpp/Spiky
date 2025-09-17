// Project Name : Spiky
// File Name    : Spiky-InitCOMStartupTask.ixx
// Author       : Felix Busch
// Created Date : 2025/09/17

export module Spiky:InitCOMStartupTask;

import Startup;

namespace Spiky
{
	struct InitCOMStartupTask : Startup::StartupTask
	{
		Continuation Setup() override;
		void Teardown() override;
	};
}