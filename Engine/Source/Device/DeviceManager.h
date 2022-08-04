#pragma once

#include <Core/Core.h>
#include "SwapChain.h"
#include "RenderTargetView.h"

namespace STL
{
	class ENGINE_API DeviceManager
	{
	public:
		DeviceManager();
		~DeviceManager();

		void Initialize(HWND handle, uint32 width, uint32 height);

		void BeginScene(const float* backgroundColor);
		void RenderScene();
		void EndScene(uint32 syncInterval, uint32 flags);
		void OnResize(uint32 width, uint32 height);
		
		// Getter.
		ID3D11Device* GetDevice() const { return device; }
		ID3D11Device** GetDeviceAddressOf() { return &device; }
		ID3D11DeviceContext* GetContext() const { return context; }
		ID3D11DeviceContext** GetContextAddressOf() { return &context; }
		
		IDXGISwapChain* GetSwapChain() { return swapChain.Get(); }
		IDXGISwapChain** GetSwapChainAddressOf() { return swapChain.GetAddressOf(); }

		ID3D11RenderTargetView* GetRenderTargetView() { return renderTargetView.Get(); }
		ID3D11RenderTargetView** GetRenderTargetViewAddressOf() { return renderTargetView.GetAddressOf(); }

	private:
		ID3D11Device* device;
		ID3D11DeviceContext* context;
		//IDXGISwapChain* swapChain;
		SwapChain swapChain;
		RenderTargetView renderTargetView;
	};
}