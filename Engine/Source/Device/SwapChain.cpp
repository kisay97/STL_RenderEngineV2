#include "Core.h"
#include "SwapChain.h"
#include <Utility/STLException.h>

namespace STL
{
	SwapChain::SwapChain()
		: swapChain(nullptr)
	{
	}

	SwapChain::~SwapChain()
	{
		SafeRelease(swapChain);
	}

	void SwapChain::Create(
		ID3D11Device* device, HWND handle, uint32 width, uint32 height, bool use4xaa, 
		uint32 numQualityLevel)
	{
		// IDXGIFactory를 얻어야함.
		// IDXGIDevice => IDXGIAdapter => IDXGIFactory.
		IDXGIDevice* dxgiDevice = nullptr;
		auto result = device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
		ThrowIfFailed(result, "Failed to get IDXGIDevice");

		IDXGIAdapter* dxgiAdapter = nullptr;
		//result = dxgiDevice->GetAdapter(&dxgiAdapter); //똑같지만 코드 통일성을 위해서(dxgiAdapter->getFactory()는 없음...). 어댑터는 많이 얻어서 따로 있다고 함.
		result = dxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&dxgiAdapter));
		ThrowIfFailed(result, "Failed to get IDXGIAdapter");
		SafeRelease(dxgiDevice);

		IDXGIFactory* dxgiFactory = nullptr;
		//result = dxgiAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&dxgiFactory));
		result = dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));
		ThrowIfFailed(result, "Failed to get IDXGIFactory");
		SafeRelease(dxgiAdapter);
		
		// 스왑 체인 생성.
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.Windowed = true;
		swapChainDesc.OutputWindow = handle;
		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = height;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		if (use4xaa)
		{
			swapChainDesc.SampleDesc.Count = 4;
			swapChainDesc.SampleDesc.Quality = numQualityLevel - 1;
		}
		else
		{
			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;
		}

		result = dxgiFactory->CreateSwapChain(device, &swapChainDesc, &swapChain);
		SafeRelease(dxgiFactory);
		ThrowIfFailed(result, "Faield to create SwapChain");
	}
	 
	void SwapChain::Present(uint32 syncInterval, uint32 flags)
	{
		swapChain->Present(syncInterval, flags);
	}
}