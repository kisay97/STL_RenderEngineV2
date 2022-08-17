#pragma once

#include <Core/Core.h>

namespace STL
{
	class ENGINE_API RasterizerState
	{
	public:
		RasterizerState();
		~RasterizerState() = default;

		void Create(ID3D11Device* devicde);
		void Bind(ID3D11DeviceContext* deviceContext);

		ID3D11RasterizerState* Get() { return rasterizerState; }
		ID3D11RasterizerState** GetAddressOf() { return &rasterizerState; }

		D3D11_FILL_MODE& FillMode() { return fillMode; }
		void SetFillMode(D3D11_FILL_MODE fillMode);

		D3D11_CULL_MODE& CullMode() { return cullMode; }
		void SetCullMode(D3D11_CULL_MODE cullMode);

	private:
		ID3D11RasterizerState* rasterizerState;
		D3D11_FILL_MODE fillMode;
		D3D11_CULL_MODE cullMode;
	};
}