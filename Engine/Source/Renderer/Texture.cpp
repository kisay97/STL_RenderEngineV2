#include "Texture.h"
#include <Utility/TextureLoader.h>

namespace STL
{
	Texture::Texture()
		: filename(L""), shaderResourceView(nullptr)
	{
	}

	Texture::Texture(const std::wstring& filename)
		: filename(filename), shaderResourceView(nullptr)
	{
	}

	Texture::~Texture()
	{
	}

	void Texture::Create(ID3D11Device* device)
	{
		// 텍스처 로딩.
		shaderResourceView = TextureLoader::CreateShaderResourceView(device, filename);
		if (shaderResourceView == nullptr)
		{
			std::stringstream ss;
			std::string filenameA;
			filenameA.assign(filename.begin(), filename.end());
			ss << "Failed to load texture with the file name: "
				<< filenameA;

			throw std::exception(ss.str().c_str());
		}
	}

	void Texture::Bind(ID3D11DeviceContext* context, uint32 index)
	{
		context->PSSetShaderResources(index, 1, &shaderResourceView);
	}
}