#pragma once

#include <Core/Core.h>

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
		
		// Getter.
		ID3D11Device* GetDevice() const { return device; }
		ID3D11Device** GetDeviceAddressOf() { return &device; }
		ID3D11DeviceContext* GetContext() const { return context; }
		ID3D11DeviceContext** GetContextAddressOf() { return &context; }
		
		IDXGISwapChain* GetSwapChain() const { return swapChain; }
		IDXGISwapChain** GetSwapChainAddressOf() { return &swapChain; }

		ID3D11RenderTargetView* GetRenderTargetView() const { return renderTargetView; }
		ID3D11RenderTargetView** GetRenderTargetViewAddressOf() { return &renderTargetView; }

	private:
		ID3D11Device* device;
		ID3D11DeviceContext* context;
		IDXGISwapChain* swapChain;
		ID3D11RenderTargetView* renderTargetView;
	};
}