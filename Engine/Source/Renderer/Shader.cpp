#include "Shader.h"

namespace STL
{
	Shader::Shader(const std::wstring& filename)
		: filename(filename), entry("main")
	{
		shaderFolderPath = std::filesystem::current_path().parent_path().append(L"Shader");
	}
	Shader::Shader(const std::wstring& filename, 
		const std::string& entry, const std::string& profile)
		: filename(filename), entry(entry), profile(profile)
	{
		shaderFolderPath = std::filesystem::current_path().parent_path().append(L"Shader");
	}
}