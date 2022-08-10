#include "DemoLevel.h"

#include <Component/Actor.h>
#include <Component/TransformComponent.h>
#include <Component/StaticMeshComponent.h>
#include <Component/CameraComponent.h>

#include <Renderer/VertexDeclaration.h>

#include <Math/MathHelper.h>

#include <Core/Application.h> // ���� ��� ����� ����.

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
			VertexPositionColorUV({-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}),		// ���� �ϴ�.
			VertexPositionColorUV({-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}),		// ���� ���.
			VertexPositionColorUV({0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}),		// ������ ���.
			VertexPositionColorUV({0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}),		// ������ �ϴ�.
		};

		uint32 indices[] = { 0,1,3,1,2,3 };

		// actor1 ����.
		Actor* actor = new Actor(device);
		//actor->Create(device);
		actor->SetPosition(-0.5f, 0.0f, 0.0f);
		actor->SetScale(0.5f, 0.5f, 1.0f);

		auto meshComponent = new StaticMeshComponent();
		meshComponent->Create(device, vertices, _countof(vertices), sizeof(vertices[0]),
			indices, _countof(indices), sizeof(uint32));
		actor->AddComponent(meshComponent);

		// actor2 ����.
		Actor* actor2 = new Actor(device);
		//actor2->Create(device);
		actor2->SetPosition(0.5f, 0.0f, 0.0f);
		actor2->SetScale(0.5f, 0.5f, 1.0f);

		auto meshComponent2 = new StaticMeshComponent();
		meshComponent2->Create(device, vertices, _countof(vertices), sizeof(vertices[0]),
			indices, _countof(indices), sizeof(uint32));
		actor2->AddComponent(meshComponent2);

		// ī�޶� �߰�.
		Actor* cameraActor = new Actor(device);
		cameraActor->SetPosition(0.0f, 0.0f, -1.0f);
		cameraActor->AddComponent(new CameraComponent(
			60.0f * MathHelper::Deg2Rad, // �þ߰� ���� (�ݰ��� 60��. ��ü 120��).
			static_cast<uint32>(engine->Width()), // ���� ũ��
			static_cast<uint32>(engine->Height()), // ���� ũ��.
			0.1f, // ����� �Ÿ�.
			1000.0f // ����� �Ÿ�.
		));

		// ī�޶� ��Ʈ�ѷ� ���� �� ������Ʈ �߰�.
		auto cameraController = new CameraController();
		cameraController->SetKeyboard(engine->GetKeyboard());
		cameraController->SetMouse(engine->GetMouse());
		cameraController->SetMoveSpeed(2.0f); // �̵� �ӵ�.
		cameraActor->AddComponent(cameraController);

		// ������ ���� �߰�
		AddActor(actor);
		AddActor(actor2);
		AddActor(cameraActor);

		Level::Initialize(device, engine);
	}
}