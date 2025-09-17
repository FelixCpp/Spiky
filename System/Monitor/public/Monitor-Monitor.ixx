module;

#include <string_view>

export module System.Monitor:Monitor;

import Math;

namespace System
{
	export struct Monitor
	{
		std::wstring_view Name;
		Math::IntBoundary WorkArea;
		Math::IntBoundary Area;
		bool IsPrimary;
	};
}