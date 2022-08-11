#include "Core.h"
#include "STLShader.h"

namespace STL
{
	STLShader::STLShader(const std::wstring& filename)
		: vertexShader(filename), pixelShader(filename)
	{
	}

	STLShader::STLShader(const std::wstring& filename, const std::string& entry)
		: vertexShader(filename, entry, "vs_5_0"), pixelShader(filename, entry, "ps_5_0")
	{
	}

	void STLShader::Initialize(ID3D11Device* device)
	{
		vertexShader.Initialize(device);
		pixelShader.Initialize(device);

		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		inputLayout.Create(device, layout, _countof(layout), GetVertexShaderBuffer());
	}

	void STLShader::Bind(ID3D11DeviceContext* deviceContext)
	{
		vertexShader.Bind(deviceContext);
		pixelShader.Bind(deviceContext);
		inputLayout.Bind(deviceContext);
	}
}