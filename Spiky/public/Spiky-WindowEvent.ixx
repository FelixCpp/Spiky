﻿// Project Name : Spiky
// File Name    : Spiky-WindowEvent.ixx
// Author       : Felix Busch
// Created Date : 2025/09/17

module;

#include <variant>

export module Spiky:WindowEvent;

export namespace Spiky
{
	class WindowEvent
	{
	private:

		template<typename... Visitors>
		struct MultiVisitor : Visitors...
		{
			using Visitors::operator()...;
		};

	public:

		struct Closed {};
		struct Resized
		{
			uint32_t Width;
			uint32_t Height;
		};

	public:

		using EventType = std::variant<Closed, Resized>;

	public:

		constexpr explicit WindowEvent(const EventType& type) :
			m_Type(type)
		{
		}

		template <typename T> [[nodiscard]] T* GetIf() { return std::get_if<T>(m_Type); }
		template <typename T> [[nodiscard]] const T* GetIf() const { return std::get_if<T>(m_Type); }
		template <typename T> [[nodiscard]] T& Get() { return std::get<T>(m_Type); }
		template <typename T> [[nodiscard]] const T& Get() const { return std::get<T>(m_Type); }
		template <typename T> [[nodiscard]] bool Is() const { return std::holds_alternative<T>(m_Type); }
		template <typename... Visitors> auto Visit(Visitors&& ... visitors) const { return std::visit(MultiVisitor<Visitors...>{ std::forward<Visitors>(visitors)... }, m_Type); }

	private:

		EventType m_Type;

	};
}