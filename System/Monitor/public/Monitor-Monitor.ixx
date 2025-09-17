module;

#include <string>

export module System.Monitor:Monitor;

import Math;

namespace System
{
	export struct Monitor
	{
		std::string Name;
		Math::IntBoundary WorkArea;
		Math::IntBoundary Area;
		bool IsPrimary;
	};
}