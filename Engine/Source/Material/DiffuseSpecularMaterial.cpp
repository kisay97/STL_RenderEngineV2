#include "Core.h"
#include "DiffuseSpecularMaterial.h"
#include <EngineShader/STLDiffuseSpecularShader.h>

namespace STL
{
	DiffuseSpecularMaterial::DiffuseSpecularMaterial()
		: Material()
	{
		shader = new STLDiffuseSpecularShader();
		materialBuffer = ConstantBuffer(&materialData, 1, sizeof(MaterialData));
		materialBuffer.SetBindShaderTarget(BindShaderTarget::PixelShader);
	}

	DiffuseSpecularMaterial::~DiffuseSpecularMaterial()
	{
	}
	
	void DiffuseSpecularMaterial::Initialize(ID3D11Device* device)
	{
		Material::Initialize(device);
		materialBuffer.Create(device);
	}

	void DiffuseSpecularMaterial::Bind(ID3D11DeviceContext* context)
	{
		Material::Bind(context);
		materialBuffer.Bind(context, 1);
	}
	
	void DiffuseSpecularMaterial::SetShiness(float shiness)
	{
		materialData.shiness = shiness;
	}
}