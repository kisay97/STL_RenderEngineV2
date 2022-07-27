#include "DeviceManager.h"
#include <Utility/STLException.h>

namespace STL
{
	DeviceManager::DeviceManager()
		: device(nullptr),
		context(nullptr)
	{
	}

	DeviceManager::~DeviceManager()
	{
		if (context != nullptr)
		{
			context->ClearState();
			SafeRelease(context);
		}

		SafeRelease(device);
		//SafeRelease(swapChain);
		//SafeRelease(renderTargetView);
	}
	
	void DeviceManager::Initialize(HWND handle, uint32 width, uint32 height)
	{
        // ��ġ ������ �� ������ �ɼ� ��.
        unsigned int createFlag = 0;

#if _DEBUG
        // Debug ����� ���,
        // ��ġ ���� �������� ������ �߻����� �� ����� ������ �� ���� �����ش޶�� �ɼ� �߰�.
        createFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

        // DX11 ���� ����.
        // ���� ������ �տ� ������ ���� �õ��غ���, �������� ������ ���� �������� �Ѿ.
        D3D_FEATURE_LEVEL levels[] =
        {
            D3D_FEATURE_LEVEL_11_1,
            D3D_FEATURE_LEVEL_11_0,
        };

        D3D_FEATURE_LEVEL finalFeature;

        // ��ġ �ʱ�ȭ.
        auto result = D3D11CreateDevice(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            createFlag,
            levels,
            //ARRAYSIZE(levels),
            _countof(levels),
            D3D11_SDK_VERSION,
            &device,
            &finalFeature,
            &context
        );

        // ���� ���� Ȯ��.
        ThrowIfFailed(result, "Failed to create device");

        // ��Ƽ ���ø� ���� ���� Ȯ��.
        uint32 m4xMSAAQuality=0;
        auto result = device->CheckMultisampleQualityLevels(
            DXGI_FORMAT_R8G8B8A8_UNORM, 
            4, 
            &m4xMSAAQuality
        );
        // ����ü�� ����.
        swapChain.Create(device, handle, width, height, true, m4xMSAAQuality);

        // ���� Ÿ�� �� ����
        renderTargetView.Create(swapChain.Get(), device);

        // ȭ��(Viewport) ����.
        D3D11_VIEWPORT viewport = {};
        viewport.TopLeftX = 0.0f;
        viewport.TopLeftY = 0.0f;
        viewport.Width = static_cast<float>(width);
        viewport.Height = static_cast<float>(height);
        viewport.MinDepth = 0.0f;
        viewport.MaxDepth = 1.0f;

        // ����Ʈ ����.
        context->RSSetViewports(1, &viewport);
	}
	
	void DeviceManager::BeginScene(const float* backgroundColor)
	{
        // ��� �����.
        //context->ClearRenderTargetView(renderTargetView, backgroundColor);
        renderTargetView.Bind(context);
        renderTargetView.Clear(context, backgroundColor);
	}
	
	void DeviceManager::RenderScene()
	{
        // TODO: �ﰢ�� �׸���
	}
	
	void DeviceManager::EndScene(uint32 syncInterval, uint32 flags)
	{
        // ȭ�� ��ȯ Front <-> Back buffer ��ȯ.
        //swapChain->Present(syncInterval, flags);
        swapChain.Present(syncInterval, flags);
	}
}