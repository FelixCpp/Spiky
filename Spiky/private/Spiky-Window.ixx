// Project Name : Spiky
// File Name    : Spiky-Window.ixx
// Author       : Felix Busch
// Created Date : 2025/09/16

module;

#include <Windows.h>

#include <string_view>
#include <variant>
#include <queue>
#include <string>
#include <optional>

export module Spiky:Window;

import Math;

namespace Spiky
{
	template<typename... Visitors>
	struct MultiVisitor : Visitors...
	{
		using Visitors::operator()...;
	};

	class WindowEvent
	{
	public:

		struct Closed {};

	public:

		using EventType = std::variant<Closed>;

	public:

		constexpr explicit WindowEvent(const EventType& type) :
			m_Type(type)
		{}

		template <typename T> [[nodiscard]] T* GetIf() { return std::get_if<T>(m_Type); }
		template <typename T> [[nodiscard]] const T* GetIf() const { return std::get_if<T>(m_Type); }
		template <typename T> [[nodiscard]] T& Get() { return std::get<T>(m_Type); }
		template <typename T> [[nodiscard]] const T& Get() const { return std::get<T>(m_Type); }
		template <typename T> [[nodiscard]] bool Is() const { return std::holds_alternative<T>(m_Type); }

		template <typename... Visitors>
		auto Visit(Visitors&& ... visitors) const { return std::visit(MultiVisitor<Visitors...>{ std::forward<Visitors>(visitors)... }, m_Type); }

	private:

		EventType m_Type;

	};

	class Window
	{
	public:

		explicit Window(int width, int height, std::string_view title);
		~Window();

		void SetVisible(bool visible);
		bool IsVisible() const;

		void SetSize(int width, int height);
		Math::Uint2 GetSize() const;

		void SetPosition(int x, int y);
		Math::Int2 GetPosition() const;

		void SetTitle(std::string_view title);
		std::string GetTitle() const;

		HWND GetNativeHandle() const;
		std::optional<WindowEvent> PollEvent();

		template <typename... Visitors>
		void HandleEvents(Visitors&& ... visitors)
		{
			while (const auto event = PollEvent())
			{
				event->Visit(std::forward<Visitors>(visitors)...);
			}
		}

	private:

		static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		void HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
		void QueueEvents() const;

		HWND m_WindowHandle;
		std::queue<WindowEvent> m_EventQueue;

	};
}