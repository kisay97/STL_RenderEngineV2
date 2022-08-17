#include "Core.h"
#include "RimNormalMappingMaterial.h"
#include <EngineShader/STLRimNormalMappingShader.h>

namespace STL
{
	RimNormalMappingMaterial::RimNormalMappingMaterial()
		: Material()
	{
		shader = new STLRimNormalMappingShader();
		constantBuffer = ConstantBuffer(&rimData, 1, sizeof(rimData));
		constantBuffer.SetBindShaderTarget(BindShaderTarget::PixelShader);
	}

	RimNormalMappingMaterial::~RimNormalMappingMaterial()
	{
	}

	void RimNormalMappingMaterial::Initialize(ID3D11Device* device)
	{
		Material::Initialize(device);
		constantBuffer.Create(device);
	}

	void RimNormalMappingMaterial::Bind(ID3D11DeviceContext* context)
	{
		Material::Bind(context);
		constantBuffer.Bind(context, 2);
	}

	void RimNormalMappingMaterial::SetRimLightColor(const Vector3f& color)
	{
		rimData.color = color;
	}

	void RimNormalMappingMaterial::SetRimConstant(float constant)
	{
		rimData.constant = constant;
	}
}