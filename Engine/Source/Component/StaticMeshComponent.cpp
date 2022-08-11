#include "Core.h"
#include "StaticMeshComponent.h"
#include <Utility/ModelLoader.h>

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

	void StaticMeshComponent::SetStaticMesh(StaticMesh* staticMesh)
	{
		this->staticMesh = staticMesh;
	}

	void StaticMeshComponent::SetStaticMesh(ID3D11Device* device, const std::string& filename)
	{
		ModelLoader::LoadModel(device, filename, staticMesh);
	}

	void StaticMeshComponent::AddMaterial(Material* newMaterial)
	{
		staticMesh->AddMaterial(newMaterial);
	}

	void StaticMeshComponent::SetMaterial(Material* newMaterial, uint32 index)
	{
		staticMesh->SetMaterial(newMaterial, index);
	}

	Material& StaticMeshComponent::GetMaterial(uint32 index)
	{
		return staticMesh->GetMaterial(index);
	}

	void StaticMeshComponent::Create(ID3D11Device* device)
	{
		staticMesh->Initialize(device);
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