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
	}

	void STLShader::Bind(ID3D11DeviceContext* deviceContext)
	{
		vertexShader.Bind(deviceContext);
		pixelShader.Bind(deviceContext);
	}
}