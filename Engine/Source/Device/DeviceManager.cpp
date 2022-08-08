#include "Core.h"
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
        // 장치 생성할 때 전달할 옵션 값.
        unsigned int createFlag = 0;

#if _DEBUG
        // Debug 모드인 경우,
        // 장치 생성 과정에서 오류가 발생했을 때 디버깅 정보를 더 많이 전달해달라는 옵션 추가.
        createFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

        // DX11 버전 지정.
        // 상위 버전을 앞에 넣으면 먼저 시도해보고, 지원하지 않으면 다음 버전으로 넘어감.
        D3D_FEATURE_LEVEL levels[] =
        {
            D3D_FEATURE_LEVEL_11_1,
            D3D_FEATURE_LEVEL_11_0,
        };

        D3D_FEATURE_LEVEL finalFeature;

        // 장치 초기화.
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

        // 실패 여부 확인.
        ThrowIfFailed(result, "Failed to create device");

        // 멀티 샘플링 지원 여부 확인.
        uint32 m4xMSAAQuality=0;
        result = device->CheckMultisampleQualityLevels(
            DXGI_FORMAT_R8G8B8A8_UNORM, 
            4, 
            &m4xMSAAQuality
        );
        // 스왑체인 생성.
        swapChain.Create(device, handle, width, height, true, m4xMSAAQuality);

        // 렌더 타겟 뷰 생성
        renderTargetView.Create(swapChain.Get(), device);

        // 뎁스 스텐실 뷰 생성.
        depthStencilView.Create(device, width, height, true, m4xMSAAQuality);

        // 화면(Viewport) 설정.
        D3D11_VIEWPORT viewport = {};
        viewport.TopLeftX = 0.0f;
        viewport.TopLeftY = 0.0f;
        viewport.Width = static_cast<float>(width);
        viewport.Height = static_cast<float>(height);
        viewport.MinDepth = 0.0f;
        viewport.MaxDepth = 1.0f;

        // 뷰포트 설정.
        context->RSSetViewports(1, &viewport);
	}
	
	void DeviceManager::BeginScene(const float* backgroundColor)
	{
        // 배경 지우기.
        //context->ClearRenderTargetView(renderTargetView, backgroundColor);
        renderTargetView.Bind(context, depthStencilView.Get());
        renderTargetView.Clear(context, backgroundColor);
        depthStencilView.Clear(context, 
            D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 
            1.0f, 0
        );
	}
	
	void DeviceManager::RenderScene()
	{
        // TODO: 삼각형 그리기
	}
	
	void DeviceManager::EndScene(uint32 syncInterval, uint32 flags)
	{
        // 화면 전환 Front <-> Back buffer 교환.
        //swapChain->Present(syncInterval, flags);
        swapChain.Present(syncInterval, flags);
	}

    void DeviceManager::OnResize(uint32 width, uint32 height)
    {
        assert(device); // == assert(device != nullptr);
        assert(context);
        assert(swapChain.Get());

        // 스왑체인의 크기가 바뀌어야 하고, 렌더타겟뷰와 뷰포트를 다시 만들어야 함.
        // 렌더 타겟 해제.
        SafeRelease(renderTargetView.Get());

        // 뎁스 스텐실 뷰 해제.
        SafeRelease(depthStencilView.Get());

        // 스왑체인의 버퍼 크기 조정.
        auto result = swapChain.Get()->ResizeBuffers(
            1, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0
        );

        // 오류 확인
        ThrowIfFailed(result, "Failed to resize swap chain");

        // 렌더타겟 재생성.
        renderTargetView.Create(swapChain.Get(), device);

        // 멀티 샘플링 지원 여부 확인.
        uint32 m4xMSAAQuality = 0;
        result = device->CheckMultisampleQualityLevels(
            DXGI_FORMAT_R8G8B8A8_UNORM,
            4,
            &m4xMSAAQuality
        );

        // 뎁스 스텐실 뷰 재생성.
        depthStencilView.Create(device, width, height, true, m4xMSAAQuality);

        // 뷰포트(화면) 생성.
        D3D11_VIEWPORT viewport = {};
        viewport.TopLeftX = 0.0f;
        viewport.TopLeftY = 0.0f;
        viewport.Width = static_cast<float>(width);
        viewport.Height = static_cast<float>(height);
        viewport.MinDepth = 0.0f;
        viewport.MaxDepth = 1.0f;

        context->RSSetViewports(1, &viewport);
    }
}