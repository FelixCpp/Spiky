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

import :Guard;
import :Logging;
import :Window;

import System.Monitor;

namespace Spiky
{
	struct LibraryData
	{
		std::unique_ptr<Window> Window;
		std::unique_ptr<Sketch> Sketch;
	};
}

module :private;

extern Spiky::LibraryData s_Data;
extern Logger s_Logger;
extern std::unique_ptr<System::MonitorProvider> s_MonitorProvider;