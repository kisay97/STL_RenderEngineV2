#include "Core.h"
#include "STLDiffuseSpecularShader.h"

namespace STL
{
	STLDiffuseSpecularShader::STLDiffuseSpecularShader()
		: STLShader()
	{
		vertexShader = VertexShader(TEXT("DiffuseSpecularVertexShader"));
		pixelShader = PixelShader(TEXT("DiffuseSpecularPixelShader"));
	}

	void STLDiffuseSpecularShader::Initialize(ID3D11Device* device)
	{
		STLShader::Initialize(device);

		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		inputLayout.Create(device, layout, _countof(layout), GetVertexShaderBuffer());
	}

	void STLDiffuseSpecularShader::Bind(ID3D11DeviceContext* deviceContext)
	{
		STLShader::Bind(deviceContext);
		inputLayout.Bind(deviceContext);
	}
}