#pragma once

#include <Core/Core.h>
#include <Renderer/ConstantBuffer.h>
#include "MaterialConstants.h"
#include "Material.h"

namespace STL
{
	class ENGINE_API RimNormalMappingMaterial : public Material
	{
	public:
		RimNormalMappingMaterial();
		~RimNormalMappingMaterial();

		virtual void Initialize(ID3D11Device* device) override;
		virtual void Bind(ID3D11DeviceContext* context) override;

		void SetRimLightColor(const Vector3f& color);
		void SetRimConstant(float constant);

	private:
		RimData rimData;
		ConstantBuffer constantBuffer;
	};
}