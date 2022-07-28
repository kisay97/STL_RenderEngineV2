#pragma once

#include <Core/Core.h>
#include <Renderer/VertexShader.h>
#include <Renderer/PixelShader.h>

namespace STL
{
	class ENGINE_API STLShader
	{
	public:
		STLShader() = default;
		STLShader(const std::wstring& filename);
		STLShader(const std::wstring& filename, const std::string& entry);
		virtual ~STLShader() = default;

		virtual void Initialize(ID3D11Device* device);
		virtual void Bind(ID3D11DeviceContext* deviceContext);

		ID3D11VertexShader* GetVertexShader() { return vertexShader.Get(); }
		ID3D11VertexShader** GetVertexShaderAddress() { return vertexShader.GetAddressOf(); }
		ID3DBlob* GetVertexShaderBuffer() { return vertexShader.ShaderBuffer(); }

		ID3D11PixelShader* GetPixelShader() { return pixelShader.Get(); }
		ID3D11PixelShader** GetPixelShaderAddress() { return pixelShader.GetAddressOf(); }
		ID3DBlob* GetPixelShaderBuffer() { return pixelShader.ShaderBuffer(); }

	protected:
		VertexShader vertexShader;
		PixelShader pixelShader;
	};
}