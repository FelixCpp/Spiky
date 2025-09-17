// Project Name : Spiky
// File Name    : Spiky.Internal-WindowStartupTask.ixx
// Author       : Felix Busch
// Created Date : 2025/09/17

module;

#include <memory>

export module Spiky.Internal:WindowStartupTask;

import Startup;
import System.Monitor;

import :Window;

export namespace Spiky::Internal
{
	class WindowStartupTask : public Startup::StartupTask
	{
	public:

		explicit WindowStartupTask(
			std::shared_ptr<Window>& window,
			std::shared_ptr<System::MonitorProvider> monitorProvider
		);

		Continuation Setup() override;
		void Teardown() override;

	private:

		std::shared_ptr<Window>& m_Window;
		std::shared_ptr<System::MonitorProvider> m_MonitorProvider;

	};
}