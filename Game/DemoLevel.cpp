#include "DemoLevel.h"

#include <Component/Actor.h>
#include <Component/TransformComponent.h>
#include <Component/StaticMeshComponent.h>

#include <Renderer/VertexDeclaration.h>

#include <Math/MathHelper.h>

namespace STL
{
	DemoLevel::DemoLevel()
		: Level()
	{
	}
	DemoLevel::~DemoLevel()
	{
	}
	void DemoLevel::Initialize(ID3D11Device* device)
	{
		VertexPositionColorUV vertices[] =
		{
			VertexPositionColorUV({-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}),		// 왼쪽 하단.
			VertexPositionColorUV({-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}),		// 왼쪽 상단.
			VertexPositionColorUV({0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}),		// 오른쪽 상단.
			VertexPositionColorUV({0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}),		// 오른쪽 하단.
		};

		uint32 indices[] = { 0,1,3,1,2,3 };

		// actor1 구성.
		Actor* actor = new Actor(device);
		actor->Create(device);
		actor->SetPosition(-0.5f, 0.0f, 0.0f);
		actor->SetScale(0.5f, 0.5f, 1.0f);

		auto meshComponent = new StaticMeshComponent();
		meshComponent->Create(device, vertices, _countof(vertices), sizeof(vertices[0]),
			indices, _countof(indices), sizeof(uint32));
		actor->AddComponent(meshComponent);

		// actor2 구성.
		Actor* actor2 = new Actor(device);
		actor2->Create(device);
		actor2->SetPosition(0.5f, 0.0f, 0.0f);
		actor2->SetScale(0.5f, 0.5f, 1.0f);

		auto meshComponent2 = new StaticMeshComponent();
		meshComponent2->Create(device, vertices, _countof(vertices), sizeof(vertices[0]),
			indices, _countof(indices), sizeof(uint32));
		actor2->AddComponent(meshComponent2);

		// 레벨에 액터 추가
		AddActor(actor);
		AddActor(actor2);
	}
}