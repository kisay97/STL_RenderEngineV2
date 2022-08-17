#pragma once

#include <Core/Core.h>
#include <Renderer/ConstantBuffer.h>
#include "MaterialConstants.h"
#include "Material.h"

namespace STL
{
	class ENGINE_API DiffuseSpecularMaterial : public Material
	{
	public:
		DiffuseSpecularMaterial();
		~DiffuseSpecularMaterial();

		virtual void Initialize(ID3D11Device* device) override;
		virtual void Bind(ID3D11DeviceContext* context) override;

		void SetShiness(float shiness);

	private:
		MaterialData materialData;
		ConstantBuffer materialBuffer;
	};
}