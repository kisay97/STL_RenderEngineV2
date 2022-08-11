#include "Core.h"
#include "Material.h"

namespace STL
{
	Material::Material()
		: index(0), shader(nullptr)
	{
	}

	Material::~Material()
	{
		for (auto texture : textures)
		{
			if (texture != nullptr)
			{
				delete texture;
				texture = nullptr;
			}
		}

		if (shader != nullptr)
		{
			delete shader;
			shader = nullptr;
		}
	}

	void Material::Initialize(ID3D11Device* device)
	{
		if (shader == nullptr)
		{
			return;
		}

		shader->Initialize(device);

		for (auto texture : textures)
		{
			texture->Create(device);
		}

		samplerState.Create(device);
	}

	void Material::Bind(ID3D11DeviceContext* context)
	{
		if (shader == nullptr)
		{
			return;
		}

		shader->Bind(context);

		for (uint32 ix = 0; ix < static_cast<uint32>(textures.size()); ++ix)
		{
			textures[ix]->Bind(context, ix);
		}

		samplerState.Bind(context, 0);
	}

	void Material::AddTexture(Texture* const newTexture)
	{
		textures.emplace_back(newTexture);
	}
}