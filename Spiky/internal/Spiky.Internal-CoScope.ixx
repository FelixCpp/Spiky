// Project Name : Spiky
// File Name    : Spiky.Internal-CoScope.ixx
// Author       : Felix Busch
// Created Date : 2025/09/17

module;

#include <functional>

export module Spiky.Internal:CoScope;

namespace Spiky::Internal
{
	export void CoScope(const std::function<void()>& callback);
}