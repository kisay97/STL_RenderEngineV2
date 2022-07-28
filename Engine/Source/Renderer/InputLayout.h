#pragma once

#include <Core/Core.h>
#include <Utility/STLException.h>

namespace STL
{
	class ENGINE_API InputLayout
	{
	public:
		InputLayout();
		~InputLayout();

		void Create(ID3D11Device* device, D3D11_INPUT_ELEMENT_DESC* layout,
			uint32 count, ID3DBlob* vertexShaderBuffer);

		void Create(ID3D11Device* device, ID3DBlob* vertexShaderBuffer);
		void Bind(ID3D11DeviceContext* context);

		ID3D11InputLayout* Get() { return inputLayout; }
		ID3D11InputLayout** GetAddressOf() { return &inputLayout; }

	private:
		ID3D11InputLayout* inputLayout;
	};
}