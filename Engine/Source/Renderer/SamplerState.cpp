#include "Core.h"
#include "SamplerState.h"
#include <Utility/STLException.h>

namespace STL
{
	SamplerState::SamplerState()
		: samplerState(nullptr)
	{
	}

	SamplerState::~SamplerState()
	{
		SafeRelease(samplerState);
	}

	void SamplerState::Create(ID3D11Device* device)
	{
		// 샘플러 스테이트 생성.
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

		auto result = device->CreateSamplerState(&samplerDesc, &samplerState);
		ThrowIfFailed(result, "Failed to create sampler state");
	}

	void SamplerState::Bind(ID3D11DeviceContext* context, uint32 index)
	{
		context->PSSetSamplers(index, 1, &samplerState);
	}
}