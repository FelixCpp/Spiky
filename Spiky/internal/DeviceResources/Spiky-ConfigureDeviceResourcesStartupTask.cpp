module;

#include <d2d1_3.h>
#include <dwrite_3.h>
#include <wincodec.h>
#include <d3d11_4.h>
#include <dxgi1_6.h>

#include <xutility>
#include <format>

module Spiky;

namespace Spiky
{
	ConfigureDeviceResourcesStartupTask::ConfigureDeviceResourcesStartupTask(
		DeviceResources* resources,
		DeviceIndependentResources* independentResources,
		DeviceResourcesScaler* scaler,
		const std::function<Window* ()>& windowProvider
	):
		m_Resources(resources),
		m_IndependentResources(independentResources),
		m_ResourcesScaler(scaler),
		m_WindowProvider(windowProvider)
	{
	}

	Startup::StartupTask::Continuation ConfigureDeviceResourcesStartupTask::Setup()
	{
		constexpr UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG;
		constexpr D3D_FEATURE_LEVEL featureLevels[] = {
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1,
		};

		D3D_FEATURE_LEVEL featureLevel;

		Microsoft::WRL::ComPtr<ID3D11Device> device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
		HRESULT hr = D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			creationFlags,
			featureLevels,
			std::size(featureLevels),
			D3D11_SDK_VERSION,
			&device,
			&featureLevel,
			&context
		);

		if (FAILED(hr))
		{
			Error("Couldn't create Direct3D device.");
			return Abort;
		}

		hr = device.As(&m_Resources->D3DDevice);
		if (FAILED(hr))
		{
			Error("Couldn't query Direct3D 11.4 device.");
			return Abort;
		}

		hr = context.As(&m_Resources->D3DContext);
		if (FAILED(hr))
		{
			Error("Couldn't query Direct3D 11.4 device context.");
			return Abort;
		}

		Microsoft::WRL::ComPtr<IDXGIDevice1> dxgiDevice;
		hr = m_Resources->D3DDevice.As(&dxgiDevice);
		if (FAILED(hr))
		{
			Error("Couldn't query DXGI device.");
			return Abort;
		}

		hr = m_IndependentResources->D2DFactory->CreateDevice(dxgiDevice.Get(), &m_Resources->D2DDevice);
		if (FAILED(hr))
		{
			Error("Couldn't create Direct2D device.");
			return Abort;
		}

		hr = m_Resources->D2DDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &m_Resources->D2DContext);
		if (FAILED(hr))
		{
			Error("Couldn't create Direct2D device context.");
			return Abort;
		}


		const auto window = m_WindowProvider();
		const auto [width, height] = window->GetSize();

		const DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {
			.Width = width,
			.Height = height,
			.Format = DXGI_FORMAT_B8G8R8A8_UNORM,
			.Stereo = FALSE,
			.SampleDesc = {.Count = 1, .Quality = 0, },
			.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT,
			.BufferCount = 2,
			.Scaling = DXGI_SCALING_NONE,
			.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL,
			.AlphaMode = DXGI_ALPHA_MODE_IGNORE,
			.Flags = 0
		};

		Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter;
		if (FAILED(dxgiDevice->GetAdapter(&dxgiAdapter)))
		{
			Error("Couldn't get DXGI adapter from DXGI device.");
			return Abort;
		}

		Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;
		if (FAILED(dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.ReleaseAndGetAddressOf()))))
		{
			Error("Couldn't get DXGI factory from DXGI adapter.");
			return Abort;
		}

		Microsoft::WRL::ComPtr<IDXGISwapChain1> dxgiSwapChain;

		if (FAILED(dxgiFactory->CreateSwapChainForHwnd(
			m_Resources->D3DDevice.Get(),
			window->GetNativeHandle(),
			&swapChainDesc,
			nullptr,
			nullptr,
			&dxgiSwapChain
		)))
		{
			Error("Couldn't create swap chain.");
			return Abort;
		}

		if (FAILED(dxgiSwapChain.As(&m_Resources->DXGISwapChain)))
		{
			Error("Couldn't query DXGI swap chain 4.");
			return Abort;
		}

		if (FAILED(dxgiDevice->SetMaximumFrameLatency(1)))
		{
			Error("Couldn't set maximum frame latency.");
			return Abort;
		}

		if (FAILED(m_Resources->DXGISwapChain->SetRotation(DXGI_MODE_ROTATION_IDENTITY)))
		{
			Error("Couldn't set swap chain rotation.");
			return Abort;
		}

		Microsoft::WRL::ComPtr<IDXGISurface> dxgiBackBuffer;
		if (FAILED(m_Resources->DXGISwapChain->GetBuffer(0, IID_PPV_ARGS(dxgiBackBuffer.ReleaseAndGetAddressOf()))))
		{
			Error("Couldn't get swap chain back buffer.");
			return Abort;
		}

		const auto bitmapProperties = D2D1::BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
			96.0f, 96.0f
		);

		if (FAILED(m_Resources->D2DContext->CreateBitmapFromDxgiSurface(dxgiBackBuffer.Get(), bitmapProperties, &m_Resources->TargetBitmap)))
		{
			Error("Couldn't create Direct2D target bitmap from DXGI surface.");
			return Abort;
		}

		m_Resources->D2DContext->SetTarget(m_Resources->TargetBitmap.Get());

		Info(std::format("Initialized device resources with feature level {}.", static_cast<int>(featureLevel)));
		return Continue;
	}

	void ConfigureDeviceResourcesStartupTask::Teardown()
	{
		m_Resources->D3DDevice.Reset();
		m_Resources->D3DContext.Reset();
		m_Resources->D2DDevice.Reset();
		m_Resources->D2DContext.Reset();
		m_Resources->DXGISwapChain.Reset();
		m_Resources->TargetBitmap.Reset();

	}
}