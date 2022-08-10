#include "DemoLevel.h"

#include <Component/Actor.h>
#include <Component/TransformComponent.h>
#include <Component/StaticMeshComponent.h>
#include <Component/CameraComponent.h>

#include <Renderer/VertexDeclaration.h>

#include <Math/MathHelper.h>

#include <Core/Application.h> // 엔진 기능 사용을 위해.

#include "CameraController.h"

namespace STL
{
	DemoLevel::DemoLevel()
		: Level()
	{
	}
	DemoLevel::~DemoLevel()
	{
	}
	void DemoLevel::Initialize(ID3D11Device* device, Application* engine)
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
		//actor->Create(device);
		actor->SetPosition(-0.5f, 0.0f, 0.0f);
		actor->SetScale(0.5f, 0.5f, 1.0f);

		auto meshComponent = new StaticMeshComponent();
		meshComponent->Create(device, vertices, _countof(vertices), sizeof(vertices[0]),
			indices, _countof(indices), sizeof(uint32));
		actor->AddComponent(meshComponent);

		// actor2 구성.
		Actor* actor2 = new Actor(device);
		//actor2->Create(device);
		actor2->SetPosition(0.5f, 0.0f, 0.0f);
		actor2->SetScale(0.5f, 0.5f, 1.0f);

		auto meshComponent2 = new StaticMeshComponent();
		meshComponent2->Create(device, vertices, _countof(vertices), sizeof(vertices[0]),
			indices, _countof(indices), sizeof(uint32));
		actor2->AddComponent(meshComponent2);

		// 카메라 추가.
		Actor* cameraActor = new Actor(device);
		cameraActor->SetPosition(0.0f, 0.0f, -1.0f);
		cameraActor->AddComponent(new CameraComponent(
			60.0f * MathHelper::Deg2Rad, // 시야각 설정 (반각이 60도. 전체 120도).
			static_cast<uint32>(engine->Width()), // 가로 크기
			static_cast<uint32>(engine->Height()), // 세로 크기.
			0.1f, // 근평면 거리.
			1000.0f // 원평면 거리.
		));

		// 카메라 컨트롤러 생성 및 컴포넌트 추가.
		auto cameraController = new CameraController();
		cameraController->SetKeyboard(engine->GetKeyboard());
		cameraController->SetMouse(engine->GetMouse());
		cameraController->SetMoveSpeed(2.0f); // 이동 속도.
		cameraActor->AddComponent(cameraController);

		// 레벨에 액터 추가
		AddActor(actor);
		AddActor(actor2);
		AddActor(cameraActor);

		Level::Initialize(device, engine);
	}
}