// Project Name : Spiky
// File Name    : Spiky-WindowUnit.ixx
// Author       : Felix Busch
// Created Date : 2025/09/16

module;

#include <string_view>
#include <string>

export module Spiky:WindowUnit;

import Math;

export namespace Spiky
{
	void ShowWindow();
	void HideWindow();
	bool IsWindowVisible();

	void SetWindowSize(int width, int height, bool recenter = true);
	Math::Uint2 GetWindowSize();
	
	void SetWindowPosition(int x, int y);
	Math::Int2 GetWindowPosition();

	void SetWindowTitle(std::string_view title);
	std::string GetWindowTitle();
}