#include "Core.h"
#include "NormalMappingMaterial.h"
#include <EngineShader/STLNormalMappingShader.h>

namespace STL
{
	NormalMappingMaterial::NormalMappingMaterial()
		: Material()
	{
		shader = new STLNormalMappingShader();
		materialBuffer = ConstantBuffer(&materialData, 1, sizeof(MaterialData));
		materialBuffer.SetBindShaderTarget(BindShaderTarget::PixelShader);
	}

	NormalMappingMaterial::~NormalMappingMaterial()
	{
	}

	void NormalMappingMaterial::Initialize(ID3D11Device* device)
	{
		Material::Initialize(device);
		materialBuffer.Create(device);
	}

	void NormalMappingMaterial::Bind(ID3D11DeviceContext* context)
	{
		Material::Bind(context);
		materialBuffer.Bind(context, 1);
	}

	void NormalMappingMaterial::SetShiness(float shiness)
	{
		materialData.shiness = shiness;
	}
}