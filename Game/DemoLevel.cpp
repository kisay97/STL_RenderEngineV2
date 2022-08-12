#include "DemoLevel.h"

#include <Component/Actor.h>
#include <Component/TransformComponent.h>
#include <Component/StaticMeshComponent.h>
#include <Component/CameraComponent.h>

#include <Renderer/VertexDeclaration.h>

#include <Math/MathHelper.h>

#include <Core/Application.h> // ���� ��� ����� ����.

#include "CameraController.h"

#include <Material/Material.h>
#include <Material/TransformMaterial.h>
#include <Material/DiffuseMaterial.h>

#include <Utility/ModelLoader.h>
#include "SoldierActor.h"
#include "SquidGameActor.h"
#include <Component/LightComponent.cpp>

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
		VertexPositionColorUVNormal vertices[] =
		{
			VertexPositionColorUVNormal({-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}),		// ���� �ϴ�.
			VertexPositionColorUVNormal({-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}),		// ���� ���.
			VertexPositionColorUVNormal({0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}),		// ������ ���.
			VertexPositionColorUVNormal({0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, -1.0f}),		// ������ �ϴ�.
		};

		uint32 indices[] = { 0,1,3,1,2,3 };

		// ��Ƽ���� ����.
		TransformMaterial* transformMaterial = new TransformMaterial();
		transformMaterial->AddTexture(new Texture(L"g4.jpg"));
		//transformMaterial->AddTexture(new Texture(L"g5.jpg"));
		transformMaterial->AddTexture(new Texture(L"gulssi.bmp"));
		materials.emplace_back(transformMaterial);

		// actor1 ����.
		Actor* actor = new Actor(device);
		actor->SetPosition(-0.5f, 0.0f, 0.0f);
		actor->SetScale(0.5f, 0.5f, 1.0f);

		auto meshComponent = new StaticMeshComponent();
		meshComponent->Create(device, vertices, _countof(vertices), sizeof(vertices[0]),
			indices, _countof(indices), sizeof(uint32));
		meshComponent->AddMaterial(transformMaterial);
		actor->AddComponent(meshComponent);

		// actor2 ����.
		Actor* actor2 = new Actor(device);
		actor2->SetPosition(0.5f, 0.0f, 0.0f);
		actor2->SetScale(0.5f, 0.5f, 1.0f);

		auto meshComponent2 = new StaticMeshComponent();
		meshComponent2->Create(device, vertices, _countof(vertices), sizeof(vertices[0]),
			indices, _countof(indices), sizeof(uint32));
		meshComponent2->AddMaterial(transformMaterial);
		actor2->AddComponent(meshComponent2);

		// ī�޶� �߰�.
		Actor* cameraActor = new Actor(device);
		cameraActor->SetPosition(0.0f, 100.0f, -200.0f);
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
		cameraController->SetMoveSpeed(100.0f); // �̵� �ӵ�.
		cameraActor->AddComponent(cameraController);

		// ����.
		// ����ƽ �޽� �ε�.
		StaticMesh* soldierMesh = new StaticMesh();
		ModelLoader::LoadModel(device, "Soldier.fbx", soldierMesh);

		// ��Ƽ���� ����.
		auto soldierBodyMaterial = new DiffuseMaterial();
		soldierBodyMaterial->AddTexture(new Texture(L"Soldier_Body_diffuse.png"));
		soldierBodyMaterial->Initialize(device);
		materials.emplace_back(soldierBodyMaterial);

		auto soldierHeadMaterial = new DiffuseMaterial();
		soldierHeadMaterial->AddTexture(new Texture(L"Soldier_head_diffuse.png"));
		soldierHeadMaterial->Initialize(device);
		materials.emplace_back(soldierHeadMaterial);

		// ���� ���� �� �ʱ�ȭ.
		//Actor* soldierActor = new Actor(device);
		//// ���Ϳ� ����ƽ �޽� ������Ʈ �߰�.
		//soldierActor->AddComponent(new StaticMeshComponent());
		//// �߰��� �޽� ������Ʈ �˻�.
		//auto soldierMeshComponent = soldierActor->GetComponent<StaticMeshComponent>();
		//// ����ƽ �޽� ������Ʈ�� ����ƽ �޽� ����.
		//soldierMeshComponent->SetStaticMesh(soldierMesh);
		//// �ʿ��� ��Ƽ���� �߰�.
		//soldierMeshComponent->AddMaterial(soldierBodyMaterial);
		//soldierMeshComponent->AddMaterial(soldierHeadMaterial);
		//soldierMeshComponent->AddMaterial(soldierBodyMaterial);

		SoldierActor* soldierActor = new SoldierActor(device);
		soldierActor->SetStaticMesh(soldierMesh);
		soldierActor->SetMaterial(soldierBodyMaterial, soldierHeadMaterial);

		// ��¡�� ���� ���� �߰�.
		// ����ƽ �޽� �ε�.
		StaticMesh* squidGameMesh = new StaticMesh();
		ModelLoader::LoadModel(device, "PinkSoldier_v01.fbx", squidGameMesh);
		
		// ��Ƽ���� ����.
		auto squidGameMat1 = new DiffuseMaterial();
		squidGameMat1->AddTexture(new Texture(L"PinkSoldier_BaseColor_1001.png"));
		materials.emplace_back(squidGameMat1);

		auto squidGameMat2 = new DiffuseMaterial();
		squidGameMat2->AddTexture(new Texture(L"PinkSoldier_BaseColor_1002.png"));
		materials.emplace_back(squidGameMat2);

		// ���� ���� �� ����.
		SquidGameActor* squidGameActor = new SquidGameActor(device);
		squidGameActor->SetPosition(200.0f, 0.0f, 0.0f);
		squidGameActor->SetStaticMesh(squidGameMesh);
		squidGameActor->SetMaterials(squidGameMat1, squidGameMat2);

		// ����Ʈ ���� ����.
		Actor* lightActor = new Actor(device);
		lightActor->SetPosition(500.0f, 500.0f, -500.0f);
		lightActor->AddComponent(new LightComponent());

		// ������ ���� �߰�
		AddActor(actor);
		AddActor(actor2);
		AddActor(cameraActor);
		AddActor(soldierActor);
		AddActor(squidGameActor);
		AddActor(lightActor);

		Level::Initialize(device, engine);
	}
}