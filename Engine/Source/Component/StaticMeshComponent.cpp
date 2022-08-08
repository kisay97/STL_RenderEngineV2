#include "Core.h"
#include "StaticMeshComponent.h"

namespace STL
{
	StaticMeshComponent::StaticMeshComponent()
		: staticMesh(nullptr)
	{
		staticMesh = new StaticMesh();
	}

	StaticMeshComponent::~StaticMeshComponent()
	{
		if (staticMesh != nullptr)
		{
			delete staticMesh;
			staticMesh = nullptr;
		}
	}

	void StaticMeshComponent::Create(ID3D11Device* device,
		void* vertices, uint32 vertexCount, uint32 vertexByteWidth,
		void* indices, uint32 indexCount, uint32 indexByteWidth)
	{
		staticMesh->Create(device,
			vertices, vertexCount, vertexByteWidth,
			indices, indexCount, indexByteWidth);
	}

	void StaticMeshComponent::Create(ID3D11Device* device)
	{
	}

	void StaticMeshComponent::Update(ID3D11DeviceContext* context, float deltaTime)
	{
	}

	void StaticMeshComponent::Bind(ID3D11DeviceContext* context)
	{
		staticMesh->Bind(context);
	}

	void StaticMeshComponent::Draw(ID3D11DeviceContext* context)
	{
		staticMesh->Draw(context);
	}
}