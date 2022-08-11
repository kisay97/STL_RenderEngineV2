#include "SoldierActor.h"

namespace STL
{
	SoldierActor::SoldierActor(ID3D11Device* device, const std::wstring& name)
		: Actor(device, name)
	{
		AddComponent(new StaticMeshComponent());
	}

	SoldierActor::~SoldierActor()
	{
	}
	
	void SoldierActor::SetStaticMesh(StaticMesh* mesh)
	{
		GetComponent<StaticMeshComponent>()->SetStaticMesh(mesh);
	}
	
	void SoldierActor::SetMaterial(Material* bodyMaterial, Material* headMaterial)
	{
		auto meshComponent = GetComponent<StaticMeshComponent>();
		meshComponent->AddMaterial(bodyMaterial);
		meshComponent->AddMaterial(headMaterial);
		meshComponent->AddMaterial(bodyMaterial);
	}
}