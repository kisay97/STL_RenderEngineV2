#pragma once

#include <Core/Core.h>
#include "Component.h"
#include <Renderer/StaticMesh.h>

namespace STL
{
	class ENGINE_API StaticMeshComponent : public Component
	{
		RTTI_DECLARATIONS(StaticMeshComponent, Component)

	public:
		StaticMeshComponent();
		~StaticMeshComponent();

		void Create(ID3D11Device* device,
			void* vertices, uint32 vertexCount, uint32 vertexByteWidth,
			void* indices, uint32 indexCount, uint32 indexByteWidth);

		void SetStaticMesh(StaticMesh* staticMesh);
		void SetStaticMesh(ID3D11Device* device, const std::string& filename);

		void AddMaterial(Material* newMaterial);
		void SetMaterial(Material* newMaterial, uint32 index);
		Material& GetMaterial(uint32 index);

		virtual void Create(ID3D11Device* device) override;
		virtual void Update(ID3D11DeviceContext* context, float deltaTime) override;
		virtual void Bind(ID3D11DeviceContext* context) override;

		void Draw(ID3D11DeviceContext* context);

	private:

		StaticMesh* staticMesh;
	};
}