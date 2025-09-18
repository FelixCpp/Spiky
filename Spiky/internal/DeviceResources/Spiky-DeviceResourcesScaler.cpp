module;

#include <d2d1_3.h>
#include <dxgi1_6.h>

#include <format>

module Spiky;

namespace Spiky
{
	DeviceResourcesScaler::DeviceResourcesScaler(DeviceResources* resources):
		m_Resources(resources)
	{
	}

	void DeviceResourcesScaler::Resize(const uint32_t width, const uint32_t height)
	{
		m_Resources->D2DContext->SetTarget(nullptr);
		m_Resources->TargetBitmap.Reset();
		m_Resources->D3DContext->Flush();

		if (FAILED(m_Resources->DXGISwapChain->ResizeBuffers(2, width, height, DXGI_FORMAT_B8G8R8A8_UNORM, 0)))
		{
			Error("Couldn't resize swap chain buffers.");
			return;
		}

		if (FAILED(m_Resources->DXGISwapChain->SetRotation(DXGI_MODE_ROTATION_IDENTITY)))
		{
			Error("Couldn't set swap chain rotation.");
			return;
		}

		Microsoft::WRL::ComPtr<IDXGISurface> dxgiBackBuffer;
		if (FAILED(m_Resources->DXGISwapChain->GetBuffer(0, IID_PPV_ARGS(dxgiBackBuffer.ReleaseAndGetAddressOf()))))
		{
			Error("Couldn't get swap chain back buffer.");
			return;
		}

		const auto bitmapProperties = D2D1::BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
			96.0f, 96.0f
		);

		if (FAILED(m_Resources->D2DContext->CreateBitmapFromDxgiSurface(dxgiBackBuffer.Get(), bitmapProperties, &m_Resources->TargetBitmap)))
		{
			Error("Couldn't create Direct2D target bitmap from DXGI surface.");
			return;
		}

		m_Resources->D2DContext->SetTarget(m_Resources->TargetBitmap.Get());
		Info(std::format("Resized device resources to {}x{}", width, height));
	}
}