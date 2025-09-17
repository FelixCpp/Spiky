// Project Name : LaunchScope
// File Name    : AppStartup.ixx
// Author       : Felix Busch
// Created Date : 2025/09/17

module;

#include <functional>
#include <memory>
#include <vector>

export module Graphics.Launch:AppStartup;

import :StartupTask;

export namespace Graphics
{
	class AppStartup
	{
	public:

		void AddStartupTask(std::unique_ptr<StartupTask> task);
		void Run(const std::function<void()>& body);

	private:

		std::vector<std::unique_ptr<StartupTask>> m_Tasks;

	};
}