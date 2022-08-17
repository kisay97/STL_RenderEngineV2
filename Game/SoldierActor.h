#pragma once

#include <Core/Core.h>
#include <Component/Actor.h>
#include <Component/StaticMeshComponent.h>
#include <Renderer/StaticMesh.h>
#include <Material/Material.h>

namespace STL
{
	class SoldierActor : public Actor
	{
	public:
		SoldierActor(ID3D11Device* device, const std::wstring& name = L"Actor");
		virtual ~SoldierActor();

		virtual void Update(ID3D11DeviceContext* context, float deltaTime = 0.f) override;

		void SetStaticMesh(StaticMesh* mesh);
		void SetMaterial(Material* bodyMaterial, Material* headMaterial);
	};
}