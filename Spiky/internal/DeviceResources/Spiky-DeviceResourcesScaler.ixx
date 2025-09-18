// Project Name : Spiky
// File Name    : Spiky-DeviceResourcesScaler.ixx
// Author       : Felix Busch
// Created Date : 2025/09/18

module;

#include <cstdint>

export module Spiky:DeviceResourcesScaler;

import :DeviceResources;
import :Window;

namespace Spiky
{
	class DeviceResourcesScaler
	{
	public:

		explicit DeviceResourcesScaler(DeviceResources* resources);
		void Resize(uint32_t width, uint32_t height);

	private:

		DeviceResources* m_Resources;

	};
}