#include "VertexShader.h"
#include <Utility/STLException.h>

namespace STL
{
	VertexShader::VertexShader()
		: VertexShader(L"VertexShader", "main", "vs_5_0")
	{
	}
	
	VertexShader::VertexShader(const std::wstring& filename)
		: VertexShader(filename, "main", "vs_5_0")
	{
	}
	
	VertexShader::VertexShader(const std::wstring& filename, const std::string& entry, const std::string& profile)
		: Shader(filename, entry, profile), vertexShader(nullptr)
	{
	}

	VertexShader::~VertexShader()
	{
		SafeRelease(shaderBuffer);
		SafeRelease(vertexShader);
	}
	
	void VertexShader::Initialize(ID3D11Device* device)
	{
		Compile(device);
		Create(device);
	}
	
	void VertexShader::Bind(ID3D11DeviceContext* context)
	{
		context->VSSetShader(vertexShader, nullptr, 0u);
	}
	
	void VertexShader::Compile(ID3D11Device* device)
	{
		uint32 compileFlags = 0u;
#if _DEBUG
		compileFlags |= D3DCOMPILE_DEBUG;
#endif

		// 쉐이더 파일 설정 (폴더 경로 포함).
		static auto folderPath = shaderFolderPath;
		static auto finalPath = folderPath.append(filename.c_str() + std::wstring(L".hlsl"));

		// HLSL 쉐이더 컴파일.
		auto result = D3DCompileFromFile(
			finalPath.c_str(),
			nullptr,
			nullptr,
			entry.c_str(),
			profile.c_str(),
			compileFlags, 0u,
			&shaderBuffer,
			nullptr
		);

		ThrowIfFailed(result, "Failed to compile vertex shader.");
	}
	
	void VertexShader::Create(ID3D11Device* device)
	{
		auto result = device->CreateVertexShader(
			shaderBuffer->GetBufferPointer(),
			shaderBuffer->GetBufferSize(),
			nullptr,
			&vertexShader
		);

		ThrowIfFailed(result, "Failed to create vertex shader.");
	}
}