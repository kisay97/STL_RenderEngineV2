#include "SoldierActor.h"
#include <Math/Vector3f.h>

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

	void SoldierActor::Update(ID3D11DeviceContext* context, float deltaTime)
	{
		Actor::Update(context, deltaTime);
		
		// 돌리고 돌리고
		//auto rotation = Rotation();
		//rotation.z -= 2880.0f * deltaTime;
		//if (rotation.z >= 360.0f || rotation.z <= -360.0f)
		//{
		//	rotation.z = 0.0f;
		//}
		//
		//SetRotation(rotation);
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