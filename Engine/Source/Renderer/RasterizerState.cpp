#include "Core.h"
#include "RasterizerState.h"
#include "Utility/STLException.h"

namespace STL
{
	RasterizerState::RasterizerState()
		: fillMode(D3D11_FILL_SOLID), 
		cullMode(D3D11_CULL_BACK), 
		rasterizerState(nullptr)
	{
	}

	void RasterizerState::Create(ID3D11Device* device)
	{
		D3D11_RASTERIZER_DESC rsDesc = {};
		rsDesc.FillMode = fillMode;
		rsDesc.CullMode = cullMode;

		HRESULT hr = device->CreateRasterizerState(&rsDesc, &rasterizerState);
		ThrowIfFailed(hr, "Failed to create rasterizer state");
	}

	void RasterizerState::Bind(ID3D11DeviceContext* deviceContext)
	{
		deviceContext->RSSetState(rasterizerState);
	}

	void RasterizerState::SetFillMode(D3D11_FILL_MODE fillMode)
	{
		this->fillMode = fillMode;
	}

	void RasterizerState::SetCullMode(D3D11_CULL_MODE cullMode)
	{
		this->cullMode = cullMode;
	}
}