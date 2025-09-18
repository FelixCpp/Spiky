module;

#include <d2d1_3.h>
#include <dwrite_3.h>
#include <wincodec.h>

module Spiky;

namespace Spiky
{
	ConfigureDeviceIndependentResourcesStartupTask::ConfigureDeviceIndependentResourcesStartupTask(DeviceIndependentResources* resources):
		m_Resources(resources)
	{
	}

	Startup::StartupTask::Continuation ConfigureDeviceIndependentResourcesStartupTask::Setup()
	{
		constexpr D2D1_FACTORY_OPTIONS d2dOptions = {
			.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION
		};

		HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, d2dOptions, m_Resources->D2DFactory.ReleaseAndGetAddressOf());
		if (FAILED(hr))
		{
			Error("Couldn't create Direct2D factory.");
			return Abort;
		}

		hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory8), reinterpret_cast<IUnknown**>(m_Resources->DWriteFactory.ReleaseAndGetAddressOf()));
		if (FAILED(hr))
		{
			Error("Couldn't create DirectWrite factory.");
			return Abort;
		}

		hr = CoCreateInstance(
			CLSID_WICImagingFactory2,
			nullptr,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(m_Resources->WICFactory.ReleaseAndGetAddressOf())
		);

		if (FAILED(hr))
		{
			Error("Couldn't create WIC Imaging factory.");
			return Abort;
		}

		Info("Successfully created device-independent resources.");
		return Continue;
	}

	void ConfigureDeviceIndependentResourcesStartupTask::Teardown()
	{
		m_Resources->D2DFactory.Reset();
		m_Resources->DWriteFactory.Reset();
		m_Resources->WICFactory.Reset();
	}
}