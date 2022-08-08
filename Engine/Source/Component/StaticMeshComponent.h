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

		virtual void Update(ID3D11DeviceContext* context, float deltaTime) override;
		virtual void Bind(ID3D11DeviceContext* context) override;

		void Draw(ID3D11DeviceContext* context);

	private:

		virtual void Create(ID3D11Device* device) override;

		StaticMesh* staticMesh;
	};
}