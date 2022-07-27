#pragma once

#include <Core/Core.h>

namespace STL
{
	class SwapChain
	{
	public:
		SwapChain();
		~SwapChain();

		void Create(ID3D11Device* device, HWND handle, uint32 width, uint32 height, bool use4xaa,
			uint32 numQualityLevel);

		void Present(uint32 syncInterval, uint32 flags);

		IDXGISwapChain* Get() { return swapChain; }
		IDXGISwapChain** GetAddressOf() { return &swapChain; }

	private:
		IDXGISwapChain* swapChain;
	};
}