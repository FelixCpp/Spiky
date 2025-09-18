// Project Name : Spiky
// File Name    : Spiky-DeviceResources.ixx
// Author       : Felix Busch
// Created Date : 2025/09/18

module;

#include <d2d1_3.h>
#include <dxgi1_6.h>
#include <d3d11_4.h>
#include <wrl/client.h>

export module Spiky:DeviceResources;

namespace Spiky
{
	struct DeviceResources
	{
		// Direct3D 11
		Microsoft::WRL::ComPtr<ID3D11Device5> D3DDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext4> D3DContext;

		// Direct2D
		Microsoft::WRL::ComPtr<ID2D1Device7> D2DDevice;
		Microsoft::WRL::ComPtr<ID2D1DeviceContext7> D2DContext;

		// DirectX Graphics Infrastructure
		Microsoft::WRL::ComPtr<IDXGISwapChain4> DXGISwapChain;
		Microsoft::WRL::ComPtr<ID2D1Bitmap1> TargetBitmap;
	};
}