// Project Name : Spiky
// File Name    : Spiky-DeviceIndependentResources.ixx
// Author       : Felix Busch
// Created Date : 2025/09/18

module;

#include <d2d1_3.h>
#include <dwrite_3.h>
#include <wincodec.h>
#include <wrl/client.h>

export module Spiky:DeviceIndependentResources;

namespace Spiky
{
	struct DeviceIndependentResources
	{
		Microsoft::WRL::ComPtr<ID2D1Factory8> D2DFactory;
		Microsoft::WRL::ComPtr<IDWriteFactory8> DWriteFactory;
		Microsoft::WRL::ComPtr<IWICImagingFactory2> WICFactory;
	};
}