module;

#include <functional>
#include <string>
#include <stdexcept>
#include <format>

export module Spiky.Internal:Guard;

import :Logging;

export namespace Spiky
{
	inline void Expect(const bool expression, const std::function<std::string()>& lazyMessage)
	{
		if (!expression)
		{
			const std::string message = std::format("Expectation failed: {}", lazyMessage());
			Error(message);
			throw std::runtime_error(message);
		}
	}

	template <typename T> requires requires(T value)
	{
		{ value == nullptr } -> std::convertible_to<bool>;
	}
	T CheckNotNull(T ptr, const std::function<std::string()>& lazyMessage)
	{
		if (ptr == nullptr)
		{
			const std::string message = std::format("Null pointer exception: {}", lazyMessage());
			Error(message);
			throw std::runtime_error(message);
		}

		return ptr;
	}
}