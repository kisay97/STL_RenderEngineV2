#pragma once

#include <Core/Core.h>

namespace STL
{
	class ENGINE_API RenderTargetView
	{
	public:
		RenderTargetView();
		~RenderTargetView();

		void Create(IDXGISwapChain* swapChain, ID3D11Device* device);
		void Bind(ID3D11DeviceContext* context, ID3D11DepthStencilView* depthStencilView);
		void Clear(ID3D11DeviceContext* context, const float* clearColor);

		ID3D11RenderTargetView* Get() { return renderTargetView; }
		ID3D11RenderTargetView** GetAddressOf() { return &renderTargetView; }
	private:
		ID3D11RenderTargetView* renderTargetView;
	};
}