#include "Core.h"
#include "PixelShader.h"
#include <Utility/STLException.h>

namespace STL
{
	PixelShader::PixelShader()
		: PixelShader(L"PixelShader", "main", "ps_5_0")
	{
	}

	PixelShader::PixelShader(const std::wstring& filename)
		: PixelShader(filename, "main", "ps_5_0")
	{
	}

	PixelShader::PixelShader(const std::wstring& filename, const std::string& entry, const std::string& profile)
		: Shader(filename, entry, profile), pixelShader(nullptr)
	{
	}

	PixelShader::~PixelShader()
	{
		SafeRelease(shaderBuffer);
		SafeRelease(pixelShader);
	}

	void PixelShader::Initialize(ID3D11Device* device)
	{
		Compile(device);
		Create(device);
	}

	void PixelShader::Bind(ID3D11DeviceContext* context)
	{
		context->PSSetShader(pixelShader, nullptr, 0u);
	}

	void PixelShader::Compile(ID3D11Device* device)
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
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			entry.c_str(),
			profile.c_str(),
			compileFlags, 0u,
			&shaderBuffer,
			nullptr
		);

		ThrowIfFailed(result, "Failed to compile pixel shader.");
	}

	void PixelShader::Create(ID3D11Device* device)
	{
		auto result = device->CreatePixelShader(
			shaderBuffer->GetBufferPointer(),
			shaderBuffer->GetBufferSize(),
			nullptr,
			&pixelShader
		);

		ThrowIfFailed(result, "Failed to create pixel shader.");
	}
}