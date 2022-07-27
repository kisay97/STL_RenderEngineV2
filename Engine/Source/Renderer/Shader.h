#pragma once

#include <Core/Core.h>

namespace STL
{
	class ENGINE_API Shader
	{
	public:
		Shader() = default;
		Shader(const std::wstring& filename);
		Shader(const std::wstring& filename, 
			const std::string& entry, const std::string& profile);
		virtual ~Shader() = default;

		virtual void Initialize(ID3D11Device* device) = 0;
		virtual void Bind(ID3D11DeviceContext* context) = 0;

		std::wstring FileName() { return filename; }
		std::string Entry() { return entry; }
		std::string Profile() { return profile; }

		ID3DBlob* ShaderBuffer() { return shaderBuffer; }
		std::filesystem::path ShaderFolderPath() { return shaderFolderPath; }

	protected:

		virtual void Compile(ID3D11Device* device) = 0;
		virtual void Create(ID3D11Device* device) = 0;

		std::wstring filename;
		std::string entry;
		std::string profile;

		ID3DBlob* shaderBuffer;
		std::filesystem::path shaderFolderPath;	// c++ 17로 설정해야함. filesystem 헤더 필요.
	};
}