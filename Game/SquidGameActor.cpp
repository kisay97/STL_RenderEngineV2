#include "SquidGameActor.h"

namespace STL
{
	SquidGameActor::SquidGameActor(ID3D11Device* device, const std::wstring& name)
		: Actor(device, name)
	{
		AddComponent(new StaticMeshComponent());
	}
	
	SquidGameActor::~SquidGameActor()
	{
	}
	
	void SquidGameActor::SetStaticMesh(StaticMesh* mesh)
	{
		GetComponent<StaticMeshComponent>()->SetStaticMesh(mesh);
	}
	
	void SquidGameActor::SetMaterials(Material* mat1, Material* mat2)
	{
		auto meshComponent = GetComponent<StaticMeshComponent>();
		meshComponent->AddMaterial(mat1);
		meshComponent->AddMaterial(mat1);
		meshComponent->AddMaterial(mat1);
		meshComponent->AddMaterial(mat1);
		meshComponent->AddMaterial(mat1);
		meshComponent->AddMaterial(mat1);

		meshComponent->AddMaterial(mat2);
		meshComponent->AddMaterial(mat2);
	}
}