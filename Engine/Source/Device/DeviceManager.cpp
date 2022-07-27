#include "DeviceManager.h"

namespace STL
{
	DeviceManager::DeviceManager()
		: device(nullptr),
		context(nullptr),
		renderTargetView(nullptr),
		swapChain(nullptr)
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
		SafeRelease(swapChain);
		SafeRelease(renderTargetView);
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

        // ��Ƽ ���ø� ���� ���� Ȯ��.
        //uint32 m4xMSAAQuality=0;
        //auto result = device->CheckMultisampleQualityLevels(
        //    DXGI_FORMAT_R8G8B8A8_UNORM, 
        //    m4xMSAAcount, 
        //    &m4xMSAAQuality
        //);

        // ����ü�� ������ ���� ����ü ����.
        DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
        swapChainDesc.BufferCount = 1;              // ����� ���� ����.
        swapChainDesc.BufferDesc.Width = width;     // ������(�̹���) ���� ũ��.
        swapChainDesc.BufferDesc.Height = height;   // ������(�̹���) ���� ũ��.
        swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;   // �̹��� ä�κ� ����.
        swapChainDesc.Windowed = true;      // â(Window) ��� ���� ����.
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;    // ������(�̹���)�� �뵵 (������).
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;    // Front<->Back ���� ������ �� ȿ�� ������ ����.
        swapChainDesc.SampleDesc.Count = 1;         // ��Ƽ ���ø� ���� ���� ���� -> ����.
        swapChainDesc.SampleDesc.Quality = 0;       // ��Ƽ ���ø� ǰ�� ���� -> �⺻ �� (Count - 1).
        swapChainDesc.OutputWindow = handle;          // DX�� �׸� â �ڵ�.

        D3D_FEATURE_LEVEL finalFeature;

        // ��ġ �ʱ�ȭ.
        auto result = D3D11CreateDeviceAndSwapChain(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            createFlag,
            levels,
            //ARRAYSIZE(levels),
            _countof(levels),
            D3D11_SDK_VERSION,
            &swapChainDesc,
            &swapChain,
            &device,
            &finalFeature,
            &context
        );

        // ���� ���� Ȯ��.
        if (FAILED(result))
        {
            MessageBox(nullptr, L"Failed to create device.", L"Error", MB_OK);
            //MessageBox(nullptr, GetErrorMessage(result).c_str(), L"Error", MB_OK);
            exit(-1);
        }

        // ����(Render, �׸���, Draw) Ÿ�� (�����) -> �츮�� �̹����� �׸� ����(�޸�).
        ID3D11Texture2D* backbuffer = nullptr;

        // �׷���ī�尡 ������ �ִ� ����� ������ ���´�.
        result = swapChain->GetBuffer(
            0,
            __uuidof(ID3D11Texture2D),
            reinterpret_cast<void**>(&backbuffer)
        );

        // ���� Ȯ��.
        if (FAILED(result))
        {
            MessageBox(nullptr, L"Failed to get back buffer.", L"Error", MB_OK);
            //MessageBox(nullptr, GetErrorMessage(result).c_str(), L"Error", MB_OK);
            exit(-1);
        }

        // ���� Ÿ�� ��(RenderTagetView) ����.
        renderTargetView = nullptr;
        result = device->CreateRenderTargetView(
            backbuffer,
            nullptr,
            &renderTargetView
        );

        // ���� Ȯ��.
        if (FAILED(result))
        {
            MessageBox(nullptr, L"Failed to create render target.", L"Error", MB_OK);
            //MessageBox(nullptr, GetErrorMessage(result).c_str(), L"Error", MB_OK);
            exit(-1);
        }

        // ����� ����.
        // COM.
        backbuffer->Release();

        // ���� Ÿ�� �� ����.
        context->OMSetRenderTargets(1, &renderTargetView, nullptr);

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
        context->ClearRenderTargetView(renderTargetView, backgroundColor);
	}
	
	void DeviceManager::RenderScene()
	{
        // TODO: �ﰢ�� �׸���
	}
	
	void DeviceManager::EndScene(uint32 syncInterval, uint32 flags)
	{
        // ȭ�� ��ȯ Front <-> Back buffer ��ȯ.
        swapChain->Present(syncInterval, flags);
	}
}