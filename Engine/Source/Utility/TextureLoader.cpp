#include "TextureLoader.h"
#include <DirectXTex.h>
#include <Utility/STLException.h>

namespace STL
{
	std::unordered_map<std::wstring, ID3D11ShaderResourceView*> TextureLoader::textureMap;

	ID3D11ShaderResourceView* TextureLoader::CreateShaderResourceView(ID3D11Device* device, const std::wstring& filename)
	{
		auto search = textureMap.find(filename);
		if (search != textureMap.end())
		{
			return search->second;
		}

		//Logger::Get().TimeStampStart();
		std::wstring extension = filename.substr(filename.find_last_of(TEXT(".")) + 1);
		std::transform(extension.begin(), extension.end(), extension.begin(), tolower);

		static auto basePath = std::filesystem::current_path().parent_path(); // current_path()는 프로젝트 폴더 그거의 parent_path()는 솔루션 폴더

		auto finalPath = basePath;
		finalPath /= "Content\\Textures"; // 리소스를 Content 폴더에 몰아넣음.
		finalPath /= filename;

		DirectX::ScratchImage image; //그림파일 읽은 정보를 저장하는 변수(정보들은 구조체 변수 목록 확인바람)
		HRESULT hr = E_FAIL;
		if (extension == TEXT("tga") || extension == TEXT("targa")) // 비압축방식 그림파일
		{
			hr = DirectX::LoadFromTGAFile(
				finalPath.c_str(),
				nullptr,
				image
			);
		}
		else //나머지들은 그냥 잘 엶
		{
			hr = DirectX::LoadFromWICFile(
				finalPath.c_str(),
				DirectX::WIC_FLAGS_NONE,
				nullptr,
				image
			);
		}

		//Logger::Get().TimeStampEnd(true);

		ThrowIfFailed(hr, "Failed to load scratch image.");

		ID3D11Texture2D* texture = nullptr;
		hr = DirectX::CreateTexture(
			device,
			image.GetImages(),
			image.GetImageCount(),
			image.GetMetadata(),
			reinterpret_cast<ID3D11Resource**>(&texture)
		);

		ThrowIfFailed(hr, "Failed to create texture.");

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		memset(&srvDesc, 0, sizeof(srvDesc));
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = 1;
		srvDesc.Format = image.GetMetadata().format;

		ID3D11ShaderResourceView* shaderResourceView = nullptr;
		hr = device->CreateShaderResourceView(
			texture,
			&srvDesc,
			&shaderResourceView
		);

		SafeRelease(texture);
		ThrowIfFailed(hr, "Failed to shader resource view.");

		textureMap.insert({ filename, shaderResourceView });

		return shaderResourceView;
	}

	void TextureLoader::Release()
	{
		for (auto pair : textureMap)
		{
			SafeRelease(pair.second);
		}
	}
}