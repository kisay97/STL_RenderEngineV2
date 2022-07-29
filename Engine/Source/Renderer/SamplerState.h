#pragma once

#include <Core/Core.h>

namespace STL
{
	class ENGINE_API SamplerState
	{
	public:
		SamplerState();
		~SamplerState();

		void Create(ID3D11Device* device);
		void Bind(ID3D11DeviceContext* context, uint32 index);

		ID3D11SamplerState* Get() { return samplerState; }
		ID3D11SamplerState** GetAddressOf() { return &samplerState; }

	private:
		ID3D11SamplerState* samplerState;
	};
}