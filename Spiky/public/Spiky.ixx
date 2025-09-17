module;

#include <functional>
#include <memory>

export module Spiky;

export import :WindowUnit;

namespace Spiky
{
	export struct Sketch
	{
		virtual ~Sketch() = default;
		virtual bool Setup() = 0;
		virtual void Draw() = 0;
		virtual void Destroy() = 0;
	};

	export int Launch(const std::function<std::unique_ptr<Sketch>()>& factory);
}

import Spiky.Internal;
import System.Monitor;

namespace Spiky
{
	struct LibraryData
	{
		std::shared_ptr<Window> Window;
		std::unique_ptr<Sketch> Sketch;
	};
}

module :private;

extern Spiky::LibraryData s_Data;
extern std::shared_ptr<Spiky::Internal::LoggingStartupTask> s_LoggingTask;
extern std::shared_ptr<System::MonitorProvider> s_MonitorProvider;