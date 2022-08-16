#pragma once

#include <Core/Core.h>
#include <Math/Vector3f.h>
#include <Renderer/ConstantBuffer.h>
#include "Material.h"
#include "DiffuseSpecularMaterial.h"

namespace STL
{
	//struct MaterialData
	//{
	//	MaterialData()
	//		: shiness(32.0f), padding()
	//	{
	//	}

	//	float shiness;
	//	Vector3f padding;
	//};

	class ENGINE_API NormalMappingMaterial : public Material
	{
	public:
		NormalMappingMaterial();
		~NormalMappingMaterial();

		virtual void Initialize(ID3D11Device* device) override;
		virtual void Bind(ID3D11DeviceContext* context) override;

		void SetShiness(float shiness);

	private:
		MaterialData materialData;
		ConstantBuffer materialBuffer;
	};
}