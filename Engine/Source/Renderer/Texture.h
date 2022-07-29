#pragma once

#include <Core/Core.h>

namespace STL
{
	class ENGINE_API Texture
	{
	public:
		Texture();
		Texture(const std::wstring& filename);
		~Texture();

		void Create(ID3D11Device* device);
		void Bind(ID3D11DeviceContext* context, uint32 index);

		ID3D11ShaderResourceView* Get() { return shaderResourceView; }
		ID3D11ShaderResourceView** GetAddressOf() { return &shaderResourceView; }

	private:
		std::wstring filename;
		ID3D11ShaderResourceView* shaderResourceView;
	};
}