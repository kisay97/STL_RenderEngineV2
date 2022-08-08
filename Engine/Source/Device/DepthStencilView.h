#pragma once

#include <Core/Core.h>

namespace STL
{
	class ENGINE_API DepthStencilView
	{
	public:
		DepthStencilView();
		~DepthStencilView();

		void Create(ID3D11Device* device,
			uint32 width, uint32 height,
			bool use4xaa, uint32 numQualityLevels
		);

		void Clear(ID3D11DeviceContext* context,
			uint32 clearFlags, float depth, uint8 stencil
		);

		ID3D11DepthStencilView* Get() { return depthStencilView; }
		ID3D11DepthStencilView** GetAddressOf() { return &depthStencilView; }

	private:
		ID3D11DepthStencilView* depthStencilView;
	};
}