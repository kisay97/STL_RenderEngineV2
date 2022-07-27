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

        // 멀티 샘플링 지원 여부 확인.
        //uint32 m4xMSAAQuality=0;
        //auto result = device->CheckMultisampleQualityLevels(
        //    DXGI_FORMAT_R8G8B8A8_UNORM, 
        //    m4xMSAAcount, 
        //    &m4xMSAAQuality
        //);

        // 스왑체인 생성을 위한 구조체 설정.
        DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
        swapChainDesc.BufferCount = 1;              // 백버퍼 개수 설정.
        swapChainDesc.BufferDesc.Width = width;     // 프레임(이미지) 가로 크기.
        swapChainDesc.BufferDesc.Height = height;   // 프레임(이미지) 세로 크기.
        swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;   // 이미지 채널별 포맷.
        swapChainDesc.Windowed = true;      // 창(Window) 모드 여부 설정.
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;    // 프레임(이미지)의 용도 (렌더링).
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;    // Front<->Back 버퍼 변경할 때 효과 넣을지 설정.
        swapChainDesc.SampleDesc.Count = 1;         // 멀티 샘플링 할지 여부 설정 -> 안함.
        swapChainDesc.SampleDesc.Quality = 0;       // 멀티 샘플링 품질 설정 -> 기본 값 (Count - 1).
        swapChainDesc.OutputWindow = handle;          // DX가 그릴 창 핸들.

        D3D_FEATURE_LEVEL finalFeature;

        // 장치 초기화.
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

        // 실패 여부 확인.
        if (FAILED(result))
        {
            MessageBox(nullptr, L"Failed to create device.", L"Error", MB_OK);
            //MessageBox(nullptr, GetErrorMessage(result).c_str(), L"Error", MB_OK);
            exit(-1);
        }

        // 렌더(Render, 그린다, Draw) 타겟 (백버퍼) -> 우리가 이미지를 그릴 버퍼(메모리).
        ID3D11Texture2D* backbuffer = nullptr;

        // 그래픽카드가 가지고 있는 백버퍼 정보를 얻어온다.
        result = swapChain->GetBuffer(
            0,
            __uuidof(ID3D11Texture2D),
            reinterpret_cast<void**>(&backbuffer)
        );

        // 오류 확인.
        if (FAILED(result))
        {
            MessageBox(nullptr, L"Failed to get back buffer.", L"Error", MB_OK);
            //MessageBox(nullptr, GetErrorMessage(result).c_str(), L"Error", MB_OK);
            exit(-1);
        }

        // 렌더 타켓 뷰(RenderTagetView) 생성.
        renderTargetView = nullptr;
        result = device->CreateRenderTargetView(
            backbuffer,
            nullptr,
            &renderTargetView
        );

        // 오류 확인.
        if (FAILED(result))
        {
            MessageBox(nullptr, L"Failed to create render target.", L"Error", MB_OK);
            //MessageBox(nullptr, GetErrorMessage(result).c_str(), L"Error", MB_OK);
            exit(-1);
        }

        // 백버퍼 해제.
        // COM.
        backbuffer->Release();

        // 렌더 타겟 뷰 설정.
        context->OMSetRenderTargets(1, &renderTargetView, nullptr);

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
        context->ClearRenderTargetView(renderTargetView, backgroundColor);
	}
	
	void DeviceManager::RenderScene()
	{
        // TODO: 삼각형 그리기
	}
	
	void DeviceManager::EndScene(uint32 syncInterval, uint32 flags)
	{
        // 화면 전환 Front <-> Back buffer 교환.
        swapChain->Present(syncInterval, flags);
	}
}