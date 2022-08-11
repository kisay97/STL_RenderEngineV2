#pragma once

#include <Core/Core.h>
#include <Component/Actor.h>
#include <Component/StaticMeshComponent.h>
#include <Renderer/StaticMesh.h>
#include <Material/Material.h>

namespace STL
{
	class SquidGameActor : public Actor
	{
	public:
		SquidGameActor(ID3D11Device* device, const std::wstring& name = L"Actor");
		virtual ~SquidGameActor();

		void SetStaticMesh(StaticMesh* mesh);
		void SetMaterials(Material* mat1, Material* mat2);
	};
}